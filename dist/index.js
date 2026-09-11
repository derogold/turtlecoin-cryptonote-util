"use strict";
// Copyright (c) 2020, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.get_block_id = exports.convert_blob_bb = exports.convert_blob = exports.construct_mm_child_block_blob = exports.construct_mm_parent_block_blob = exports.get_merged_mining_nonce_size = exports.construct_block_blob = exports.address_decode = void 0;
/** @ignore */
const native = require('bindings')('cryptonote.node');
/**
 * Calculates the address prefix in decimal form from the given address
 * @param address the public wallet address to decode
 */
function address_decode(address) {
    return native.address_decode(address);
}
exports.address_decode = address_decode;
/**
 * Constructs a new "final" block that can be submitted to the network
 * from the original block in the block template and the nonce value
 * found by the miner(s)
 * @param block the block template blob
 * @param nonce
 */
function construct_block_blob(block, nonce) {
    if (!(nonce instanceof Buffer)) {
        const tmp = Buffer.alloc(4);
        tmp.writeUInt32LE(nonce, 0);
        nonce = tmp;
    }
    return native.construct_block_blob(block, nonce);
}
exports.construct_block_blob = construct_block_blob;
/**
 * Returns the extra nonce bytes needed to reserve space for a merged mining tag
 */
function get_merged_mining_nonce_size() {
    return native.get_merged_mining_nonce_size();
}
exports.get_merged_mining_nonce_size = get_merged_mining_nonce_size;
/**
 * Constructs a parent block template that commits to both parent and child
 * auxiliary blocks through the merged mining tag.
 */
function construct_mm_parent_block_blob(parentBlock, childBlock, parentGenesisHash, childGenesisHash) {
    return native.construct_mm_parent_block_blob(parentBlock, childBlock, parentGenesisHash, childGenesisHash);
}
exports.construct_mm_parent_block_blob = construct_mm_parent_block_blob;
/**
 * Constructs a child block blob from a mined parent share and the original
 * child block template.
 */
function construct_mm_child_block_blob(parentShare, childBlock, parentGenesisHash, childGenesisHash) {
    return native.construct_mm_child_block_blob(parentShare, childBlock, parentGenesisHash, childGenesisHash);
}
exports.construct_mm_child_block_blob = construct_mm_child_block_blob;
/**
 * Converts a block into a v1 hashing block typically used by miners during
 * mining operations. This method actually creates a merged mining block
 * that merge mines itself
 * @param template the block template blob
 */
function convert_blob(template) {
    return native.convert_blob(template);
}
exports.convert_blob = convert_blob;
/**
 * Legacy convert block (prior to merged mining) that parses and validates
 * a block blob from a block template
 * @param template the block template blob
 */
function convert_blob_bb(template) {
    return native.convert_blob_bb(template);
}
exports.convert_blob_bb = convert_blob_bb;
/**
 * Calculates the block id (hash) of the given blob
 * @param blob the block blob
 */
function get_block_id(blob) {
    return native.get_block_id(blob);
}
exports.get_block_id = get_block_id;
/**
 * Provides CryptoNote based utilities for block manipulation using a
 * native Node.js c++ addon. The methods in this class are provided
 * as async primitives that wrap the synchronous versions for those
 * that wish to use Typescript
 */
class CryptoNoteUtils {
    /**
     * Calculates the address prefix in decimal form from the given address
     * @param address the public wallet address to decode
     */
    static address_decode(address) {
        return __awaiter(this, void 0, void 0, function* () {
            const l_address = Buffer.from(address);
            return address_decode(l_address);
        });
    }
    /**
     * Constructs a new "final" block that can be submitted to the network
     * from the original block in the block template and the nonce value
     * found by the miner(s)
     * @param block the block blob
     * @param nonce
     */
    static construct_block_blob(block, nonce) {
        return __awaiter(this, void 0, void 0, function* () {
            return construct_block_blob(block, nonce);
        });
    }
    /**
     * Returns the extra nonce bytes needed to reserve space for a merged mining tag
     */
    static get_merged_mining_nonce_size() {
        return __awaiter(this, void 0, void 0, function* () {
            return get_merged_mining_nonce_size();
        });
    }
    /**
     * Constructs a parent block template that commits to both parent and child
     * auxiliary blocks through the merged mining tag.
     */
    static construct_mm_parent_block_blob(parentBlock, childBlock, parentGenesisHash, childGenesisHash) {
        return __awaiter(this, void 0, void 0, function* () {
            return construct_mm_parent_block_blob(parentBlock, childBlock, parentGenesisHash, childGenesisHash);
        });
    }
    /**
     * Constructs a child block blob from a mined parent share and the original
     * child block template.
     */
    static construct_mm_child_block_blob(parentShare, childBlock, parentGenesisHash, childGenesisHash) {
        return __awaiter(this, void 0, void 0, function* () {
            return construct_mm_child_block_blob(parentShare, childBlock, parentGenesisHash, childGenesisHash);
        });
    }
    /**
     * Converts a block into a v1 hashing block typically used by miners during
     * mining operations. This method actually creates a merged mining block
     * that merge mines itself
     * @param template the block template blob
     */
    static convert_blob(template) {
        return __awaiter(this, void 0, void 0, function* () {
            return convert_blob(template);
        });
    }
    /**
     * Legacy convert block (prior to merged mining) that parses and validates
     * a block blob from a block template
     * @param template the block template blob
     */
    static convert_blob_bb(template) {
        return __awaiter(this, void 0, void 0, function* () {
            return convert_blob_bb(template);
        });
    }
    /**
     * Calculates the block id (hash) of the given blob
     * @param blob the block blob
     */
    static get_block_id(blob) {
        return __awaiter(this, void 0, void 0, function* () {
            return get_block_id(blob);
        });
    }
}
exports.default = CryptoNoteUtils;
