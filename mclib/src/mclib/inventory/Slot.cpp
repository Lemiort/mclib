#include <mclib/inventory/Slot.h>

#include <mclib/common/DataBuffer.h>

namespace mc {
namespace inventory {

Slot Slot::FromNBT(nbt::TagCompound& compound) {
    uint8_t count = 0;
    int16_t id = -1;
    int16_t damage = 0;
    nbt::NBT nbt;

    for (auto iter = compound.begin(); iter != compound.end(); ++iter) {
        auto tag = iter->second;
        if (tag->GetName() == L"Count") {
            count = ((nbt::TagByte*)tag.get())->GetValue();
        } else if (tag->GetName() == L"Damage") {
            damage = ((nbt::TagShort*)tag.get())->GetValue();
        } else if (tag->GetName() == L"id") {
            id = ((nbt::TagShort*)tag.get())->GetValue();
        } else if (tag->GetName() == L"tag") {
            nbt::TagCompound* newRoot = ((nbt::TagCompound*)tag.get());

            nbt.SetRoot(*newRoot);
        }
    }

    return Slot(id, count, damage, nbt);
}

DataBuffer Slot::Serialize(protocol::Version version) const {
    DataBuffer out;

    if (version > protocol::Version::Minecraft_1_12_2) {
        if (m_ItemId >= 0) {
            VarInt id(m_ItemId);

            out << true << id << m_ItemCount;

            if (m_NBT.HasData()) {
                out << m_NBT;
            } else {
                out << (uint8_t)0;
            }
        } else {
            out << false;
        }
    } else {
        out << m_ItemId;
        if (m_ItemId == -1) return out;

        out << m_ItemCount << m_ItemDamage;

        if (m_NBT.HasData()) {
            out << m_NBT;
        } else {
            out << (uint8_t)0;
        }
    }

    return out;
}

void Slot::Deserialize(DataBuffer& in, protocol::Version version) {
    m_ItemId = -1;
    m_ItemCount = 0;
    m_ItemDamage = 0;

    if (version > protocol::Version::Minecraft_1_12_2) {
        bool present;

        in >> present;

        if (!present) return;

        VarInt itemId;

        in >> itemId >> m_ItemCount >> m_NBT;

        m_ItemId = itemId.GetInt();
    } else {
        int16_t id;

        in >> id;

        m_ItemId = id;

        if (m_ItemId == -1) {
            m_ItemCount = 0;
            m_ItemDamage = 0;
            return;
        }

        in >> m_ItemCount;
        in >> m_ItemDamage;

        uint8_t hasNBT;
        in >> hasNBT;

        if (hasNBT) {
            in.SetReadOffset(in.GetReadOffset() - 1);
            in >> m_NBT;
        }
    }
}

}  // namespace inventory
}  // namespace mc
