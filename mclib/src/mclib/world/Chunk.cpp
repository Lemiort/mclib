#include <mclib/world/Chunk.h>

#include <mclib/common/DataBuffer.h>

#include <algorithm>

namespace mc {
namespace world {

Chunk::Chunk() { m_BitsPerBlock = 4; }

Chunk::Chunk(const Chunk& other) {
    m_Data = other.m_Data;
    m_BitsPerBlock = other.m_BitsPerBlock;
}

Chunk& Chunk::operator=(const Chunk& other) {
    m_Data = other.m_Data;
    m_BitsPerBlock = other.m_BitsPerBlock;
    return *this;
}

void Chunk::Load(DataBuffer& in, ChunkColumnMetadata* meta,
                 int32_t chunkIndex) {
    in >> m_BitsPerBlock;

    VarInt paletteLength;
    in >> paletteLength;

    m_Palette.reserve(paletteLength.GetInt());

    for (int32_t i = 0; i < paletteLength.GetInt(); ++i) {
        VarInt paletteValue;
        in >> paletteValue;
        m_Palette.push_back((uint16_t)paletteValue.GetInt());
    }

    VarInt dataArrayLength;
    in >> dataArrayLength;

    m_Data.resize(dataArrayLength.GetInt());

    for (int32_t i = 0; i < dataArrayLength.GetInt(); ++i) {
        uint64_t data;
        in >> data;
        m_Data[i] = data;
    }

    static const int64_t lightSize = 16 * 16 * 16 / 2;

    // Block light data
    in.SetReadOffset(in.GetReadOffset() + lightSize);
    // TODO add light parsing here

    // Sky Light
    if (meta->skylight) {
        in.SetReadOffset(in.GetReadOffset() + lightSize);
    }
}

block::BlockPtr Chunk::GetBlock(Vector3i chunkPosition) const {
    if (chunkPosition.x < 0 || chunkPosition.x > 15 || chunkPosition.y < 0 ||
        chunkPosition.y > 15 || chunkPosition.z < 0 || chunkPosition.z > 15) {
        return block::BlockRegistry::GetInstance()->GetBlock(0);
    }

    const std::size_t index = (std::size_t)(
        chunkPosition.y * 16 * 16 + chunkPosition.z * 16 + chunkPosition.x);
    const int32_t bitIndex = index * m_BitsPerBlock;
    const int32_t startIndex = bitIndex / 64;
    const int32_t endIndex = (((index + 1) * m_BitsPerBlock) - 1) / 64;
    const int32_t startSubIndex = bitIndex % 64;

    const int64_t maxValue = (1 << m_BitsPerBlock) - 1;
    uint32_t value;

    if (startIndex == endIndex) {
        value = (uint32_t)((m_Data[startIndex] >> startSubIndex) & maxValue);
    } else {
        const int32_t endSubIndex = 64 - startSubIndex;

        value = (uint32_t)(((m_Data[startIndex] >> startSubIndex) |
                            (m_Data[endIndex] << endSubIndex)) &
                           maxValue);
    }

    const uint16_t blockType = m_BitsPerBlock < 9 ? m_Palette[value] : value;

    return block::BlockRegistry::GetInstance()->GetBlock(blockType);
}

void Chunk::SetBlock(Vector3i chunkPosition, block::BlockPtr block) {
    std::size_t index = (std::size_t)(chunkPosition.y * 16 * 16 +
                                      chunkPosition.z * 16 + chunkPosition.x);
    int32_t bitIndex = index * m_BitsPerBlock;
    int32_t startIndex = bitIndex / 64;
    int32_t endIndex = (((index + 1) * m_BitsPerBlock) - 1) / 64;
    int32_t startSubIndex = bitIndex % 64;

    int64_t maxValue = (1 << m_BitsPerBlock) - 1;
    uint32_t blockType = block->GetType();

    if (m_BitsPerBlock == 0) {
        m_BitsPerBlock = 4;
    }

    if (m_Data.empty()) {
        m_Palette.push_back(0);
        uint32_t size = (16 * 16 * 16) * m_BitsPerBlock / 64;

        m_Data.resize(size);
        memset(&m_Data[0], 0, size * sizeof(m_Data[0]));
    }

    auto iter = std::find_if(
        m_Palette.begin(), m_Palette.end(),
        [blockType](uint32_t ptype) { return ptype == blockType; });

    if (iter == m_Palette.end())
        iter = m_Palette.insert(m_Palette.end(), blockType);

    int32_t value = std::distance(m_Palette.begin(), iter);

    // Erase old value in data entry and OR with new data
    m_Data[startIndex] = (m_Data[startIndex] & ~(maxValue << startSubIndex)) |
                         (((int64_t)value & maxValue) << startSubIndex);

    if (startIndex != endIndex) {
        int32_t endSubIndex = 64 - startSubIndex;

        // Erase beginning of data and then OR with new data
        m_Data[endIndex] = (m_Data[endIndex] >> endSubIndex << endSubIndex) |
                           ((int64_t)value & maxValue) >> endSubIndex;
    }
}

ChunkColumn::ChunkColumn(ChunkColumnMetadata metadata) : m_Metadata(metadata) {
    for (std::size_t i = 0; i < m_Chunks.size(); ++i) m_Chunks[i] = nullptr;
}

block::BlockPtr ChunkColumn::GetBlock(Vector3i position) {
    int32_t chunkIndex = (int32_t)(position.y / 16);
    Vector3i relativePosition(position.x, position.y % 16, position.z);

    if (chunkIndex < 0 || chunkIndex > 15 || !m_Chunks[chunkIndex])
        return block::BlockRegistry::GetInstance()->GetBlock(0);

    return m_Chunks[chunkIndex]->GetBlock(relativePosition);
}

block::BlockEntityPtr ChunkColumn::GetBlockEntity(Vector3i worldPos) {
    auto iter = m_BlockEntities.find(worldPos);
    if (iter == m_BlockEntities.end()) return nullptr;
    return iter->second;
}

std::vector<block::BlockEntityPtr> ChunkColumn::GetBlockEntities() {
    std::vector<block::BlockEntityPtr> blockEntities;

    for (auto iter = m_BlockEntities.begin(); iter != m_BlockEntities.end();
         ++iter)
        blockEntities.push_back(iter->second);

    return blockEntities;
}

DataBuffer& operator>>(DataBuffer& in, ChunkColumn& column) {
    ChunkColumnMetadata* meta = &column.m_Metadata;

    for (int16_t i = 0; i < ChunkColumn::ChunksPerColumn; ++i) {
        // The section mask says whether or not there is data in this chunk.
        if (meta->sectionmask & (1 << i)) {
            column.m_Chunks[i] = std::make_shared<Chunk>();

            column.m_Chunks[i]->Load(in, meta, i);
        } else {
            // Air section, leave null
            column.m_Chunks[i] = nullptr;
        }
    }

    return in;
}

}  // namespace world
}  // namespace mc
