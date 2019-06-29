#ifndef MCLIB_BLOCK_FLOWERPOT_H_
#define MCLIB_BLOCK_FLOWERPOT_H_

#include <mclib/block/BlockEntity.h>

#include <unordered_map>

namespace mc {
namespace block {

class FlowerPot : public BlockEntity {
private:
    std::wstring m_ItemId;
    int32_t m_ItemData;

public:
    MCLIB_API FlowerPot(BlockEntityType type, Vector3i position)
        : BlockEntity(type, position) {}
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);

    inline const std::wstring& GetItemId() const noexcept { return m_ItemId; }
    inline int32_t GetItemData() const noexcept { return m_ItemData; }
};

}  // namespace block
}  // namespace mc

#endif
