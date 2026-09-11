/// <reference types="node" />
/**
 * Calculates the address prefix in decimal form from the given address
 * @param address the public wallet address to decode
 */
export declare function address_decode(address: Buffer): number;
/**
 * Constructs a new "final" block that can be submitted to the network
 * from the original block in the block template and the nonce value
 * found by the miner(s)
 * @param block the block template blob
 * @param nonce
 */
export declare function construct_block_blob(block: Buffer, nonce: Buffer | number): Buffer;
/**
 * Returns the extra nonce bytes needed to reserve space for a merged mining tag
 */
export declare function get_merged_mining_nonce_size(): number;
/**
 * Constructs a parent block template that commits to both parent and child
 * auxiliary blocks through the merged mining tag.
 */
export declare function construct_mm_parent_block_blob(parentBlock: Buffer, childBlock: Buffer, parentGenesisHash: Buffer, childGenesisHash: Buffer): Buffer;
/**
 * Constructs a child block blob from a mined parent share and the original
 * child block template.
 */
export declare function construct_mm_child_block_blob(parentShare: Buffer, childBlock: Buffer, parentGenesisHash: Buffer, childGenesisHash: Buffer): Buffer;
/**
 * Converts a block into a v1 hashing block typically used by miners during
 * mining operations. This method actually creates a merged mining block
 * that merge mines itself
 * @param template the block template blob
 */
export declare function convert_blob(template: Buffer): Buffer;
/**
 * Legacy convert block (prior to merged mining) that parses and validates
 * a block blob from a block template
 * @param template the block template blob
 */
export declare function convert_blob_bb(template: Buffer): Buffer;
/**
 * Calculates the block id (hash) of the given blob
 * @param blob the block blob
 */
export declare function get_block_id(blob: Buffer): Buffer;
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
    static address_decode(address: Buffer): Promise<number>;
    /**
     * Constructs a new "final" block that can be submitted to the network
     * from the original block in the block template and the nonce value
     * found by the miner(s)
     * @param block the block blob
     * @param nonce
     */
    static construct_block_blob(block: Buffer, nonce: Buffer | number): Promise<Buffer>;
    /**
     * Returns the extra nonce bytes needed to reserve space for a merged mining tag
     */
    static get_merged_mining_nonce_size(): Promise<number>;
    /**
     * Constructs a parent block template that commits to both parent and child
     * auxiliary blocks through the merged mining tag.
     */
    static construct_mm_parent_block_blob(parentBlock: Buffer, childBlock: Buffer, parentGenesisHash: Buffer, childGenesisHash: Buffer): Promise<Buffer>;
    /**
     * Constructs a child block blob from a mined parent share and the original
     * child block template.
     */
    static construct_mm_child_block_blob(parentShare: Buffer, childBlock: Buffer, parentGenesisHash: Buffer, childGenesisHash: Buffer): Promise<Buffer>;
    /**
     * Converts a block into a v1 hashing block typically used by miners during
     * mining operations. This method actually creates a merged mining block
     * that merge mines itself
     * @param template the block template blob
     */
    static convert_blob(template: Buffer): Promise<Buffer>;
    /**
     * Legacy convert block (prior to merged mining) that parses and validates
     * a block blob from a block template
     * @param template the block template blob
     */
    static convert_blob_bb(template: Buffer): Promise<Buffer>;
    /**
     * Calculates the block id (hash) of the given blob
     * @param blob the block blob
     */
    static get_block_id(blob: Buffer): Promise<Buffer>;
}
