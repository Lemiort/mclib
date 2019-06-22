#ifndef MCLIB_BLOCK_NOTEBLOCK_H_
#define MCLIB_BLOCK_NOTEBLOCK_H_

#include <mclib/block/BlockEntity.h>

#include <unordered_map>

namespace mc {
namespace block {

class NoteBlock : public BlockEntity {
private:
    uint8_t m_Note;
    uint8_t m_Powered;

public:
    MCLIB_API NoteBlock(BlockEntityType type, Vector3i position)
        : BlockEntity(type, position) {}
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);

    inline uint8_t GetNode() const noexcept { return m_Note; }
    inline bool IsPowered() const noexcept { return m_Powered != 0; }
};

}  // namespace block
}  // namespace mc

#endif
