#ifndef MCLIB_BLOCK_MONSTERSPAWNER_H_
#define MCLIB_BLOCK_MONSTERSPAWNER_H_

#include <mclib/block/BlockEntity.h>

#include <unordered_map>

namespace mc {
namespace block {

class MonsterSpawner : public BlockEntity {
public:
    struct SpawnPotential {
        std::wstring type;
        int32_t weight;
    };

private:
    std::vector<SpawnPotential> m_SpawnPotentials;
    std::wstring m_EntityId;
    int16_t m_SpawnCount;
    int16_t m_SpawnRange;
    int16_t m_Delay;
    int16_t m_MinSpawnDelay;
    int16_t m_MaxSpawnDelay;
    int16_t m_MaxNearbyEntities;
    int16_t m_RequiredPlayerRange;

public:
    MCLIB_API MonsterSpawner(BlockEntityType type, Vector3i position)
        : BlockEntity(type, position) {}
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);

    inline const std::vector<SpawnPotential>& GetSpawnPotentials() const
        noexcept {
        return m_SpawnPotentials;
    }
    inline const std::wstring& GetEntityId() const noexcept {
        return m_EntityId;
    }
    inline int16_t GetSpawnCount() const noexcept { return m_SpawnCount; }
    inline int16_t GetSpawnRange() const noexcept { return m_SpawnRange; }
    inline int16_t GetDelay() const noexcept { return m_Delay; }
    inline int16_t GetMinSpawnDelay() const noexcept { return m_MinSpawnDelay; }
    inline int16_t GetMaxSpawnDelay() const noexcept { return m_MaxSpawnDelay; }
    inline int16_t GetMaxNearbyEntities() const noexcept {
        return m_MaxNearbyEntities;
    }
    inline int16_t GetRequiredPlayerRange() const noexcept {
        return m_RequiredPlayerRange;
    }
};

}  // namespace block
}  // namespace mc

#endif
