// Copyright (c) 2020, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

/** @ignore */
const native = require('bindings')('cryptonote.node');

/**
 * Calculates the address prefix in decimal form from the given address
 * @param address the public wallet address to decode
 */
export function address_decode (address: Buffer): number {
    return native.address_decode(address);
}

/**
 * Constructs a new "final" block that can be submitted to the network
 * from the original block in the block template and the nonce value
 * found by the miner(s)
 * @param block the block template blob
 * @param nonce
 */
export function construct_block_blob(block: Buffer, nonce: Buffer | number): Buffer {
    if (!(nonce instanceof Buffer)) {
        const tmp = Buffer.alloc(4);

        tmp.writeUInt32LE(nonce, 0);

        nonce = tmp;
    }

    return native.construct_block_blob(block, nonce);
}

/**
 * Returns the extra nonce bytes needed to reserve space for a merged mining tag
 */
export function get_merged_mining_nonce_size(): number {
    return native.get_merged_mining_nonce_size();
}

/**
 * Constructs a parent block template that commits to both parent and child
 * auxiliary blocks through the merged mining tag.
 */
export function construct_mm_parent_block_blob(
    parentBlock: Buffer,
    childBlock: Buffer,
    parentGenesisHash: Buffer,
    childGenesisHash: Buffer
): Buffer {
    return native.construct_mm_parent_block_blob(parentBlock, childBlock, parentGenesisHash, childGenesisHash);
}

/**
 * Constructs a child block blob from a mined parent share and the original
 * child block template.
 */
export function construct_mm_child_block_blob(
    parentShare: Buffer,
    childBlock: Buffer,
    parentGenesisHash: Buffer,
    childGenesisHash: Buffer
): Buffer {
    return native.construct_mm_child_block_blob(parentShare, childBlock, parentGenesisHash, childGenesisHash);
}

/**
 * Converts a block into a v1 hashing block typically used by miners during
 * mining operations. This method actually creates a merged mining block
 * that merge mines itself
 * @param template the block template blob
 */
export function convert_blob(template: Buffer): Buffer {
    return native.convert_blob(template)
}

/**
 * Legacy convert block (prior to merged mining) that parses and validates
 * a block blob from a block template
 * @param template the block template blob
 */
export function convert_blob_bb(template: Buffer): Buffer {
    return native.convert_blob_bb(template);
}

/**
 * Calculates the block id (hash) of the given blob
 * @param blob the block blob
 */
export function get_block_id(blob: Buffer): Buffer {
    return native.get_block_id(blob);
}

/**
 * Provides CryptoNote based utilities for block manipulation using a
 * native Node.js c++ addon. The methods in this class are provided
 * as async primitives that wrap the synchronous versions for those
 * that wish to use Typescript
 */
export default class CryptoNoteUtils {
    /**
     * Calculates the address prefix in decimal form from the given address
     * @param address the public wallet address to decode
     */
    public static async address_decode(address: Buffer): Promise<number> {
        const l_address = Buffer.from(address);

        return address_decode(l_address);
    }

    /**
     * Constructs a new "final" block that can be submitted to the network
     * from the original block in the block template and the nonce value
     * found by the miner(s)
     * @param block the block blob
     * @param nonce
     */
    public static async construct_block_blob(block: Buffer, nonce: Buffer | number): Promise<Buffer> {
        return construct_block_blob(block, nonce);
    }

    /**
     * Returns the extra nonce bytes needed to reserve space for a merged mining tag
     */
    public static async get_merged_mining_nonce_size(): Promise<number> {
        return get_merged_mining_nonce_size();
    }

    /**
     * Constructs a parent block template that commits to both parent and child
     * auxiliary blocks through the merged mining tag.
     */
    public static async construct_mm_parent_block_blob(
        parentBlock: Buffer,
        childBlock: Buffer,
        parentGenesisHash: Buffer,
        childGenesisHash: Buffer
    ): Promise<Buffer> {
        return construct_mm_parent_block_blob(parentBlock, childBlock, parentGenesisHash, childGenesisHash);
    }

    /**
     * Constructs a child block blob from a mined parent share and the original
     * child block template.
     */
    public static async construct_mm_child_block_blob(
        parentShare: Buffer,
        childBlock: Buffer,
        parentGenesisHash: Buffer,
        childGenesisHash: Buffer
    ): Promise<Buffer> {
        return construct_mm_child_block_blob(parentShare, childBlock, parentGenesisHash, childGenesisHash);
    }

    /**
     * Converts a block into a v1 hashing block typically used by miners during
     * mining operations. This method actually creates a merged mining block
     * that merge mines itself
     * @param template the block template blob
     */
    public static async convert_blob(template: Buffer): Promise<Buffer> {
        return convert_blob(template);
    }

    /**
     * Legacy convert block (prior to merged mining) that parses and validates
     * a block blob from a block template
     * @param template the block template blob
     */
    public static async convert_blob_bb(template: Buffer): Promise<Buffer> {
        return convert_blob_bb(template);
    }

    /**
     * Calculates the block id (hash) of the given blob
     * @param blob the block blob
     */
    public static async get_block_id(blob: Buffer): Promise<Buffer> {
        return get_block_id(blob);
    }
}
