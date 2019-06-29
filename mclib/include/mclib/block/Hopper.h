#ifndef MCLIB_BLOCK_HOPPER_H_
#define MCLIB_BLOCK_HOPPER_H_

#include <mclib/block/BlockEntity.h>
#include <mclib/block/InventoryBlock.h>
#include <mclib/common/Nameable.h>

#include <unordered_map>

namespace mc {
namespace block {

class Hopper : public BlockEntity, public InventoryBlock, public Nameable {
private:
    int32_t m_TransferCooldown;

public:
    MCLIB_API Hopper(BlockEntityType type, Vector3i position)
        : BlockEntity(type, position) {}
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);

    int32_t GetTransferCooldown() const noexcept { return m_TransferCooldown; }
};

}  // namespace block
}  // namespace mc

#endif
