#if !defined(_WIN32)
#include <cmath>
#endif

#include <chrono>
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include <string>
#include <algorithm>
#include <cstring>
#include <limits>
#include "cryptonote_core/cryptonote_basic.h"
#include "cryptonote_core/cryptonote_format_utils.h"
#include "cryptonote_protocol/blobdatatype.h"
#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "common/base58.h"
#include "serialization/binary_utils.h"
#include <nan.h>

namespace cryptonoteutil {
using namespace node;
using namespace v8;
using namespace cryptonote;

void THROW_ERROR_EXCEPTION(const char* msg) {
    return Nan::ThrowError(msg);
}

blobdata uint64be_to_blob(uint64_t num) {
    blobdata res = "        ";
    res[0] = num >> 56 & 0xff;
    res[1] = num >> 48 & 0xff;
    res[2] = num >> 40 & 0xff;
    res[3] = num >> 32 & 0xff;
    res[4] = num >> 24 & 0xff;
    res[5] = num >> 16 & 0xff;
    res[6] = num >> 8  & 0xff;
    res[7] = num       & 0xff;
    return res;
}


static bool fillExtra(cryptonote::block& block1, const cryptonote::block& block2) {
    cryptonote::tx_extra_merge_mining_tag mm_tag;
    mm_tag.depth = 0;
    if (!cryptonote::get_block_header_hash(block2, mm_tag.merkle_root))
        return false;

    block1.miner_tx.extra.clear();
    if (!cryptonote::append_mm_tag_to_extra(block1.miner_tx.extra, mm_tag))
        return false;

    return true;
}

static bool fillExtraWithMergeRoot(cryptonote::block& block1, const crypto::hash& merkle_root, size_t depth) {
    cryptonote::tx_extra_merge_mining_tag mm_tag;
    mm_tag.depth = depth;
    mm_tag.merkle_root = merkle_root;

    block1.miner_tx.extra.clear();
    if (!cryptonote::append_mm_tag_to_extra(block1.miner_tx.extra, mm_tag))
        return false;

    return true;
}

static bool mergeBlocks(const cryptonote::block& block1, cryptonote::block& block2, const std::vector<crypto::hash>& branch2) {
    block2.timestamp = block1.timestamp;
    block2.parent_block.major_version = block1.major_version;
    block2.parent_block.minor_version = block1.minor_version;
    block2.parent_block.prev_id = block1.prev_id;
    block2.parent_block.nonce = block1.nonce;
    block2.parent_block.miner_tx = block1.miner_tx;
    block2.parent_block.number_of_transactions = block1.tx_hashes.size() + 1;
    block2.parent_block.miner_tx_branch.resize(crypto::tree_depth(block1.tx_hashes.size() + 1));
    std::vector<crypto::hash> transactionHashes;
    transactionHashes.push_back(cryptonote::get_transaction_hash(block1.miner_tx));
    std::copy(block1.tx_hashes.begin(), block1.tx_hashes.end(), std::back_inserter(transactionHashes));
    tree_branch(transactionHashes.data(), transactionHashes.size(), block2.parent_block.miner_tx_branch.data());
    block2.parent_block.blockchain_branch = branch2;
    return true;
}

static bool construct_parent_block(const cryptonote::block& b, cryptonote::block& parent_block) {
    parent_block.major_version = 1;
    parent_block.minor_version = 0;
    parent_block.timestamp = b.timestamp;
    parent_block.prev_id = b.prev_id;
    parent_block.nonce = b.parent_block.nonce;
    parent_block.miner_tx.version = CURRENT_TRANSACTION_VERSION;
    parent_block.miner_tx.unlock_time = 0;

    return fillExtra(parent_block, b);
}

static bool construct_parent_block_with_merge_root(const cryptonote::block& b, const crypto::hash& merkle_root, size_t depth, cryptonote::block& parent_block) {
    parent_block.major_version = 1;
    parent_block.minor_version = 0;
    parent_block.timestamp = b.timestamp;
    parent_block.prev_id = b.prev_id;
    parent_block.nonce = b.parent_block.nonce;
    parent_block.miner_tx.version = CURRENT_TRANSACTION_VERSION;
    parent_block.miner_tx.unlock_time = 0;

    return fillExtraWithMergeRoot(parent_block, merkle_root, depth);
}

static bool readBufferArgument(Nan::NAN_METHOD_ARGS_TYPE info, int index, const char* message, Local<Object>& target) {
    if (info.Length() <= index)
        return false;

    target = info[index]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());
    if (!Buffer::HasInstance(target)) {
        THROW_ERROR_EXCEPTION(message);
        return false;
    }

    return true;
}

static bool readHashArgument(Nan::NAN_METHOD_ARGS_TYPE info, int index, const char* message, crypto::hash& hash) {
    Local<Object> target;
    if (!readBufferArgument(info, index, message, target))
        return false;

    if (Buffer::Length(target) != sizeof(crypto::hash)) {
        THROW_ERROR_EXCEPTION(message);
        return false;
    }

    std::memcpy(&hash, Buffer::Data(target), sizeof(crypto::hash));
    return true;
}

static size_t mergeMiningPath(const crypto::hash& genesis_hash, size_t depth) {
    const uint8_t* path = reinterpret_cast<const uint8_t*>(&genesis_hash);
    size_t result = 0;
    for (size_t bit = 0; bit < depth; bit++) {
        if (path[bit >> 3] & (1 << (bit & 7)))
            result |= static_cast<size_t>(1) << bit;
    }
    return result;
}

static void hashPair(const crypto::hash& left, const crypto::hash& right, crypto::hash& output) {
    crypto::hash pair[2];
    pair[0] = left;
    pair[1] = right;
    crypto::cn_fast_hash(pair, sizeof(pair), output);
}

static bool buildMergeMiningBranches(
    const crypto::hash& parent_header_hash,
    const crypto::hash& child_header_hash,
    const crypto::hash& parent_genesis_hash,
    const crypto::hash& child_genesis_hash,
    crypto::hash& merkle_root,
    std::vector<crypto::hash>& parent_branch,
    std::vector<crypto::hash>& child_branch
) {
    const size_t max_depth = 8 * sizeof(crypto::hash);
    size_t depth = 1;
    for (; depth <= max_depth; depth++) {
        if (mergeMiningPath(parent_genesis_hash, depth) != mergeMiningPath(child_genesis_hash, depth))
            break;
    }

    if (depth > max_depth || depth >= sizeof(size_t) * 8)
        return false;

    const size_t leaf_count = static_cast<size_t>(1) << depth;
    std::vector<std::vector<crypto::hash>> levels;
    levels.reserve(depth + 1);
    levels.push_back(std::vector<crypto::hash>(leaf_count, cryptonote::null_hash));

    const size_t parent_path = mergeMiningPath(parent_genesis_hash, depth);
    const size_t child_path = mergeMiningPath(child_genesis_hash, depth);
    levels[0][parent_path] = parent_header_hash;
    levels[0][child_path] = child_header_hash;

    for (size_t level = 0; level < depth; level++) {
        const std::vector<crypto::hash>& current = levels[level];
        std::vector<crypto::hash> next(current.size() / 2);
        for (size_t i = 0; i < current.size(); i += 2) {
            hashPair(current[i], current[i + 1], next[i / 2]);
        }
        levels.push_back(next);
    }

    merkle_root = levels[depth][0];
    parent_branch.assign(depth, cryptonote::null_hash);
    child_branch.assign(depth, cryptonote::null_hash);

    size_t parent_index = parent_path;
    size_t child_index = child_path;
    for (size_t level = 0; level < depth; level++) {
        parent_branch[depth - 1 - level] = levels[level][parent_index ^ 1];
        child_branch[depth - 1 - level] = levels[level][child_index ^ 1];
        parent_index >>= 1;
        child_index >>= 1;
    }

    crypto::hash check_root;
    crypto::tree_hash_from_branch(parent_branch.data(), parent_branch.size(), parent_header_hash, &parent_genesis_hash, check_root);
    if (check_root != merkle_root)
        return false;
    crypto::tree_hash_from_branch(child_branch.data(), child_branch.size(), child_header_hash, &child_genesis_hash, check_root);
    return check_root == merkle_root;
}

NAN_METHOD(convert_blob) {

    if (info.Length() < 1)
        return THROW_ERROR_EXCEPTION("You must provide one argument.");

    Local<Object> target = info[0]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());

    if (!Buffer::HasInstance(target))
        return THROW_ERROR_EXCEPTION("Argument should be a buffer object.");

    blobdata input = std::string(Buffer::Data(target), Buffer::Length(target));
    blobdata output = "";

    //convert
    block b = AUTO_VAL_INIT(b);
    if (!parse_and_validate_block_from_blob(input, b))
        return THROW_ERROR_EXCEPTION("Failed to parse block");

    if (b.major_version < BLOCK_MAJOR_VERSION_2) {
        if (!get_block_hashing_blob(b, output))
            return THROW_ERROR_EXCEPTION("Failed to create mining block");
    } else {
        block parent_block;
        if (!construct_parent_block(b, parent_block))
            return THROW_ERROR_EXCEPTION("Failed to construct parent block");

        if (!get_block_hashing_blob(parent_block, output))
            return THROW_ERROR_EXCEPTION("Failed to create mining block");
    }

    v8::Local<v8::Value> returnValue = Nan::CopyBuffer((char*)output.data(), output.size()).ToLocalChecked();
    info.GetReturnValue().Set(returnValue);
}


NAN_METHOD(get_block_id) {

    if (info.Length() < 1)
        return THROW_ERROR_EXCEPTION("You must provide one argument.");

    Local<Object> target = info[0]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());

    if (!Buffer::HasInstance(target))
        return THROW_ERROR_EXCEPTION("Argument should be a buffer object.");

    blobdata input = std::string(Buffer::Data(target), Buffer::Length(target));
    blobdata output = "";

    block b = AUTO_VAL_INIT(b);
    if (!parse_and_validate_block_from_blob(input, b))
        return THROW_ERROR_EXCEPTION("Failed to parse block");

    crypto::hash block_id;
    if (!get_block_hash(b, block_id))
        return THROW_ERROR_EXCEPTION("Failed to calculate hash for block");

    char *cstr = reinterpret_cast<char*>(&block_id);
    v8::Local<v8::Value> returnValue = Nan::CopyBuffer(cstr, 32).ToLocalChecked();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(get_merged_mining_nonce_size) {
    const size_t mm_nonce_size = 1 + 2 + sizeof(crypto::hash);
    info.GetReturnValue().Set(Nan::New(static_cast<uint32_t>(mm_nonce_size)));
}

NAN_METHOD(construct_mm_parent_block_blob) {
    if (info.Length() < 4)
        return THROW_ERROR_EXCEPTION("You must provide parent block, child block, parent genesis hash, and child genesis hash.");

    int child_arg = 1;
    if (info[1]->IsNumber())
        child_arg = 2;

    Local<Object> parent_template_buf;
    Local<Object> child_template_buf;
    if (!readBufferArgument(info, 0, "Parent block should be a buffer object.", parent_template_buf))
        return THROW_ERROR_EXCEPTION("You must provide a parent block.");
    if (!readBufferArgument(info, child_arg, "Child block should be a buffer object.", child_template_buf))
        return;

    crypto::hash parent_genesis_hash;
    crypto::hash child_genesis_hash;
    if (!readHashArgument(info, child_arg + 1, "Parent genesis hash should be a 32-byte buffer.", parent_genesis_hash))
        return;
    if (!readHashArgument(info, child_arg + 2, "Child genesis hash should be a 32-byte buffer.", child_genesis_hash))
        return;

    blobdata parent_template_blob = std::string(Buffer::Data(parent_template_buf), Buffer::Length(parent_template_buf));
    blobdata child_template_blob = std::string(Buffer::Data(child_template_buf), Buffer::Length(child_template_buf));
    blobdata output = "";

    block parent = AUTO_VAL_INIT(parent);
    block child = AUTO_VAL_INIT(child);
    if (!parse_and_validate_block_from_blob(parent_template_blob, parent))
        return THROW_ERROR_EXCEPTION("Failed to parse parent block");
    if (!parse_and_validate_block_from_blob(child_template_blob, child))
        return THROW_ERROR_EXCEPTION("Failed to parse child block");
    if (parent.major_version < BLOCK_MAJOR_VERSION_2 || child.major_version < BLOCK_MAJOR_VERSION_2)
        return THROW_ERROR_EXCEPTION("Merged mining helpers require v2+ blocks.");

    crypto::hash parent_header_hash;
    crypto::hash child_header_hash;
    if (!get_block_header_hash(parent, parent_header_hash))
        return THROW_ERROR_EXCEPTION("Failed to calculate parent header hash");
    if (!get_block_header_hash(child, child_header_hash))
        return THROW_ERROR_EXCEPTION("Failed to calculate child header hash");

    crypto::hash merkle_root;
    std::vector<crypto::hash> parent_branch;
    std::vector<crypto::hash> child_branch;
    if (!buildMergeMiningBranches(parent_header_hash, child_header_hash, parent_genesis_hash, child_genesis_hash, merkle_root, parent_branch, child_branch))
        return THROW_ERROR_EXCEPTION("Failed to construct merged mining merkle tree");

    block parent_block;
    if (!construct_parent_block_with_merge_root(parent, merkle_root, parent_branch.size(), parent_block))
        return THROW_ERROR_EXCEPTION("Failed to construct parent block");

    if (!mergeBlocks(parent_block, parent, parent_branch))
        return THROW_ERROR_EXCEPTION("Failed to postprocess parent block");

    if (!block_to_blob(parent, output))
        return THROW_ERROR_EXCEPTION("Failed to convert parent block to blob");

    v8::Local<v8::Value> returnValue = Nan::CopyBuffer((char*)output.data(), output.size()).ToLocalChecked();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(construct_mm_child_block_blob) {
    if (info.Length() < 4)
        return THROW_ERROR_EXCEPTION("You must provide mined parent block, child block, parent genesis hash, and child genesis hash.");

    int child_arg = 1;
    if (info[1]->IsNumber())
        child_arg = 2;

    Local<Object> parent_share_buf;
    Local<Object> child_template_buf;
    if (!readBufferArgument(info, 0, "Mined parent block should be a buffer object.", parent_share_buf))
        return THROW_ERROR_EXCEPTION("You must provide a mined parent block.");
    if (!readBufferArgument(info, child_arg, "Child block should be a buffer object.", child_template_buf))
        return;

    crypto::hash parent_genesis_hash;
    crypto::hash child_genesis_hash;
    if (!readHashArgument(info, child_arg + 1, "Parent genesis hash should be a 32-byte buffer.", parent_genesis_hash))
        return;
    if (!readHashArgument(info, child_arg + 2, "Child genesis hash should be a 32-byte buffer.", child_genesis_hash))
        return;

    blobdata parent_share_blob = std::string(Buffer::Data(parent_share_buf), Buffer::Length(parent_share_buf));
    blobdata child_template_blob = std::string(Buffer::Data(child_template_buf), Buffer::Length(child_template_buf));
    blobdata output = "";

    block parent_share = AUTO_VAL_INIT(parent_share);
    block child = AUTO_VAL_INIT(child);
    if (!parse_and_validate_block_from_blob(parent_share_blob, parent_share))
        return THROW_ERROR_EXCEPTION("Failed to parse mined parent block");
    if (!parse_and_validate_block_from_blob(child_template_blob, child))
        return THROW_ERROR_EXCEPTION("Failed to parse child block");
    if (parent_share.major_version < BLOCK_MAJOR_VERSION_2 || child.major_version < BLOCK_MAJOR_VERSION_2)
        return THROW_ERROR_EXCEPTION("Merged mining helpers require v2+ blocks.");

    crypto::hash parent_header_hash;
    crypto::hash child_header_hash;
    if (!get_block_header_hash(parent_share, parent_header_hash))
        return THROW_ERROR_EXCEPTION("Failed to calculate parent header hash");
    if (!get_block_header_hash(child, child_header_hash))
        return THROW_ERROR_EXCEPTION("Failed to calculate child header hash");

    crypto::hash merkle_root;
    std::vector<crypto::hash> parent_branch;
    std::vector<crypto::hash> child_branch;
    if (!buildMergeMiningBranches(parent_header_hash, child_header_hash, parent_genesis_hash, child_genesis_hash, merkle_root, parent_branch, child_branch))
        return THROW_ERROR_EXCEPTION("Failed to construct merged mining merkle tree");

    cryptonote::tx_extra_merge_mining_tag mm_tag;
    if (!cryptonote::get_mm_tag_from_extra(parent_share.parent_block.miner_tx.extra, mm_tag))
        return THROW_ERROR_EXCEPTION("Merged mining tag not found in parent block");
    if (mm_tag.depth != parent_branch.size() || mm_tag.merkle_root != merkle_root)
        return THROW_ERROR_EXCEPTION("Parent block merged mining tag does not match child template");

    child.timestamp = parent_share.timestamp;
    child.parent_block = parent_share.parent_block;
    child.parent_block.blockchain_branch = child_branch;

    if (!block_to_blob(child, output))
        return THROW_ERROR_EXCEPTION("Failed to convert child block to blob");

    v8::Local<v8::Value> returnValue = Nan::CopyBuffer((char*)output.data(), output.size()).ToLocalChecked();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(construct_block_blob) {

    if (info.Length() < 2)
        return THROW_ERROR_EXCEPTION("You must provide two arguments.");

    Local<Object> block_template_buf = info[0]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());

    Local<Object> nonce_buf = info[1]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());

    if (!Buffer::HasInstance(block_template_buf) || !Buffer::HasInstance(nonce_buf))
        return THROW_ERROR_EXCEPTION("Both arguments should be buffer objects.");

    if (Buffer::Length(nonce_buf) != 4)
        return THROW_ERROR_EXCEPTION("Nonce buffer has invalid size.");

    uint32_t nonce = *reinterpret_cast<uint32_t*>(Buffer::Data(nonce_buf));

    blobdata block_template_blob = std::string(Buffer::Data(block_template_buf), Buffer::Length(block_template_buf));
    blobdata output = "";

    block b = AUTO_VAL_INIT(b);
    if (!parse_and_validate_block_from_blob(block_template_blob, b))
        return THROW_ERROR_EXCEPTION("Failed to parse block");

    b.nonce = nonce;
    if (b.major_version >= BLOCK_MAJOR_VERSION_2) {
        b.parent_block.nonce = nonce;

        cryptonote::tx_extra_merge_mining_tag existing_mm_tag;
        if (!cryptonote::get_mm_tag_from_extra(b.parent_block.miner_tx.extra, existing_mm_tag) || existing_mm_tag.depth == 0) {
            block parent_block;
            if (!construct_parent_block(b, parent_block))
                return THROW_ERROR_EXCEPTION("Failed to construct parent block");

            if (!mergeBlocks(parent_block, b, std::vector<crypto::hash>()))
                return THROW_ERROR_EXCEPTION("Failed to postprocess mining block");
        }
    }

    if (!block_to_blob(b, output))
        return THROW_ERROR_EXCEPTION("Failed to convert block to blob");

    v8::Local<v8::Value> returnValue = Nan::CopyBuffer((char*)output.data(), output.size()).ToLocalChecked();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(convert_blob_bb) {

    if (info.Length() < 1)
        return THROW_ERROR_EXCEPTION("You must provide one argument.");

    Local<Object> target = info[0]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());

    if (!Buffer::HasInstance(target))
        return THROW_ERROR_EXCEPTION("Argument should be a buffer object.");

    blobdata input = std::string(Buffer::Data(target), Buffer::Length(target));
    blobdata output = "";

    //convert
    bb_block b = AUTO_VAL_INIT(b);
    if (!parse_and_validate_block_from_blob(input, b)) {
        return THROW_ERROR_EXCEPTION("Failed to parse block");
    }
    output = get_block_hashing_blob(b);

    v8::Local<v8::Value> returnValue = Nan::CopyBuffer((char*)output.data(), output.size()).ToLocalChecked();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(address_decode) {

    if (info.Length() < 1)
        return THROW_ERROR_EXCEPTION("You must provide one argument.");

    Local<Object> target = info[0]->ToObject(Nan::GetCurrentContext()).FromMaybe(Local<Object>());

    if (!Buffer::HasInstance(target))
        return THROW_ERROR_EXCEPTION("Argument should be a buffer object.");

    blobdata input = std::string(Buffer::Data(target), Buffer::Length(target));

    blobdata data;
    uint64_t prefix;
    if (!tools::base58::decode_addr(input, prefix, data)) {
        info.GetReturnValue().Set(Nan::Undefined());
    }

    account_public_address adr;
    if (!::serialization::parse_binary(data, adr)) {
        info.GetReturnValue().Set(Nan::Undefined());
    }

    if (!crypto::check_key(adr.m_spend_public_key) || !crypto::check_key(adr.m_view_public_key)) {
        info.GetReturnValue().Set(Nan::Undefined());
    }

    info.GetReturnValue().Set(Nan::New(static_cast<uint32_t>(prefix)));
}

NAN_MODULE_INIT(Init) {
    Nan::Set(target, Nan::New("construct_block_blob").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(construct_block_blob)).ToLocalChecked());
    Nan::Set(target, Nan::New("get_block_id").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(get_block_id)).ToLocalChecked());
    Nan::Set(target, Nan::New("convert_blob").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(convert_blob)).ToLocalChecked());
    Nan::Set(target, Nan::New("convert_blob_bb").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(convert_blob_bb)).ToLocalChecked());
    Nan::Set(target, Nan::New("address_decode").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(address_decode)).ToLocalChecked());
    Nan::Set(target, Nan::New("get_merged_mining_nonce_size").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(get_merged_mining_nonce_size)).ToLocalChecked());
    Nan::Set(target, Nan::New("construct_mm_parent_block_blob").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(construct_mm_parent_block_blob)).ToLocalChecked());
    Nan::Set(target, Nan::New("construct_mm_child_block_blob").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(construct_mm_child_block_blob)).ToLocalChecked());
}

NODE_MODULE(cryptonote, Init)
}
