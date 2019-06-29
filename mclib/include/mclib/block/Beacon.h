#ifndef MCLIB_BLOCK_BEACON_H_
#define MCLIB_BLOCK_BEACON_H_

#include <mclib/block/BlockEntity.h>

#include <unordered_map>

namespace mc {
namespace block {

class Beacon : public BlockEntity {
private:
    std::wstring m_Lock;
    int32_t m_Levels;
    int32_t m_Primary;
    int32_t m_Secondary;

public:
    MCLIB_API Beacon(BlockEntityType type, Vector3i position)
        : BlockEntity(type, position),
          m_Levels(0),
          m_Primary(0),
          m_Secondary(0) {}
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);

    int32_t GetLevels() const noexcept { return m_Levels; }
    int32_t GetPrimary() const noexcept { return m_Primary; }
    int32_t GetSecondary() const noexcept { return m_Secondary; }
};

}  // namespace block
}  // namespace mc

#endif
