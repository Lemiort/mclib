#ifndef MCLIB_BLOCK_REDSTONECOMPARATOR_H_
#define MCLIB_BLOCK_REDSTONECOMPARATOR_H_

#include <mclib/block/BlockEntity.h>

#include <unordered_map>

namespace mc {
namespace block {

class RedstoneComparator : public BlockEntity {
private:
    int32_t m_OutputSignal;

public:
    MCLIB_API RedstoneComparator(BlockEntityType type, Vector3i position)
        : BlockEntity(type, position) {}
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);

    inline int32_t GetOutputSignal() const noexcept { return m_OutputSignal; }
};

}  // namespace block
}  // namespace mc

#endif
