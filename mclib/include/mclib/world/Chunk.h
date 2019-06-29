#ifndef MCLIB_WORLD_CHUNK_H_
#define MCLIB_WORLD_CHUNK_H_

#include "mclib/block/Block.h"
#include "mclib/block/BlockEntity.h"
#include "mclib/common/Types.h"
#include "mclib/nbt/NBT.h"

#include <array>
#include <map>
#include <memory>

namespace mc {

class DataBuffer;

namespace world {

struct ChunkColumnMetadata {
    int32_t x;
    int32_t z;
    uint16_t sectionmask;
    bool continuous;
    bool skylight;
};

/**
 * A 16x16x16 area. A ChunkColumn is made up of 16 of these
 */
class Chunk {
private:
    uint8_t m_BitsPerBlock;
    std::vector<uint32_t> m_Palette;
    std::vector<uint64_t> m_Data;
    // std::vector<uint8_t> m_BlockLight;  // TODO
    // std::optional<std::vector<uint8_t>> m_SkyLight;  // TODO
public:
    MCLIB_API Chunk();

    MCLIB_API Chunk(const Chunk& other);
    MCLIB_API Chunk& operator=(const Chunk& other);
    /**
     * Position is relative to this chunk position
     */
    block::BlockPtr MCLIB_API GetBlock(Vector3i chunkPosition) const;

    /**
     * Position is relative to this chunk position
     */
    void MCLIB_API SetBlock(Vector3i chunkPosition, block::BlockPtr block);

    /**
     * chunkIndex is the index (0-16) of this chunk in the ChunkColumn
     */
    void MCLIB_API Load(DataBuffer& in, ChunkColumnMetadata* meta,
                        int32_t chunkIndex);
};

using ChunkPtr = std::shared_ptr<Chunk>;

/**
 * Stores a 16x256x16 area. Uses chunks (16x16x16) to store the data vertically.
 * A null chunk is fully air.
 */
class ChunkColumn {
public:
    enum { ChunksPerColumn = 16 };

    using iterator = std::array<ChunkPtr, ChunksPerColumn>::iterator;
    using reference = std::array<ChunkPtr, ChunksPerColumn>::reference;
    using const_iterator =
        std::array<ChunkPtr, ChunksPerColumn>::const_iterator;
    using const_reference =
        std::array<ChunkPtr, ChunksPerColumn>::const_reference;

private:
    std::array<ChunkPtr, ChunksPerColumn> m_Chunks;
    ChunkColumnMetadata m_Metadata;
    std::map<Vector3i, block::BlockEntityPtr> m_BlockEntities;

public:
    MCLIB_API ChunkColumn(ChunkColumnMetadata metadata);

    ChunkColumn(const ChunkColumn& rhs) = default;
    ChunkColumn& operator=(const ChunkColumn& rhs) = default;
    ChunkColumn(ChunkColumn&& rhs) = default;
    ChunkColumn& operator=(ChunkColumn&& rhs) = default;

    iterator MCLIB_API begin() { return m_Chunks.begin(); }

    iterator MCLIB_API end() { return m_Chunks.end(); }

    reference MCLIB_API operator[](std::size_t index) {
        return m_Chunks[index];
    }

    const_iterator MCLIB_API begin() const { return m_Chunks.begin(); }

    const_iterator MCLIB_API end() const { return m_Chunks.end(); }

    const_reference MCLIB_API operator[](std::size_t index) const {
        return m_Chunks[index];
    }

    void MCLIB_API AddBlockEntity(block::BlockEntityPtr blockEntity) {
        m_BlockEntities.insert(
            std::make_pair(blockEntity->GetPosition(), blockEntity));
    }

    void RemoveBlockEntity(Vector3i pos) { m_BlockEntities.erase(pos); }

    /**
     * Position is relative to this ChunkColumn position.
     */
    block::BlockPtr MCLIB_API GetBlock(Vector3i position);
    const ChunkColumnMetadata& GetMetadata() const { return m_Metadata; }

    MCLIB_API block::BlockEntityPtr GetBlockEntity(Vector3i worldPos);
    std::vector<block::BlockEntityPtr> MCLIB_API GetBlockEntities();

    friend MCLIB_API DataBuffer& operator>>(DataBuffer& in,
                                            ChunkColumn& column);
};

typedef std::shared_ptr<ChunkColumn> ChunkColumnPtr;

MCLIB_API DataBuffer& operator>>(DataBuffer& in, ChunkColumn& column);

}  // namespace world
}  // namespace mc

#endif
