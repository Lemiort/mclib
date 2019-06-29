#ifndef MCLIB_INVENTORY_SLOT_H_
#define MCLIB_INVENTORY_SLOT_H_

#include <mclib/common/Types.h>
#include <mclib/mclib.h>
#include <mclib/nbt/NBT.h>
#include <mclib/protocol/ProtocolState.h>

namespace mc {

class DataBuffer;

namespace inventory {

class Slot {
private:
    nbt::NBT m_NBT;
    int32_t m_ItemId;
    int16_t m_ItemDamage;
    uint8_t m_ItemCount;

public:
    Slot() noexcept : m_ItemId(-1), m_ItemCount(0), m_ItemDamage(0) {}
    Slot(int32_t itemId, uint8_t itemCount, int16_t itemDamage) noexcept
        : m_ItemId(itemId),
          m_ItemCount(itemCount),
          m_ItemDamage(itemDamage),
          m_NBT() {}

    Slot(int32_t itemId, uint8_t itemCount, int16_t itemDamage,
         nbt::NBT nbt) noexcept
        : m_ItemId(itemId),
          m_ItemCount(itemCount),
          m_ItemDamage(itemDamage),
          m_NBT(nbt) {}

    Slot(const Slot& rhs) = default;
    Slot& operator=(const Slot& rhs) = default;
    Slot(Slot&& rhs) = default;
    Slot& operator=(Slot&& rhs) = default;

    int32_t GetItemId() const noexcept { return m_ItemId; }
    uint8_t GetItemCount() const noexcept { return m_ItemCount; }
    int16_t GetItemDamage() const noexcept { return m_ItemDamage; }
    const nbt::NBT& GetNBT() const noexcept { return m_NBT; }

    static MCLIB_API Slot FromNBT(nbt::TagCompound& compound);

    DataBuffer Serialize(protocol::Version version) const;
    void Deserialize(DataBuffer& in, protocol::Version version);
};

}  // namespace inventory
}  // namespace mc

#endif
