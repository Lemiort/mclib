#ifndef MCLIB_INVENTORY_INVENTORY_H_
#define MCLIB_INVENTORY_INVENTORY_H_

#include <mclib/core/Connection.h>
#include <mclib/inventory/Slot.h>
#include <mclib/protocol/packets/PacketHandler.h>

#include <memory>

namespace mc {
namespace inventory {

class Inventory {
public:
    static const MCLIB_API int32_t HOTBAR_SLOT_START;
    static const MCLIB_API int32_t PLAYER_INVENTORY_ID;

    using ItemMap = std::map<int32_t, Slot>;

private:
    ItemMap m_Items;
    int m_WindowId;
    int16_t m_CurrentAction;
    Slot m_Cursor;

    MCLIB_API void HandleTransaction(core::Connection& conn, uint16_t action,
                                     bool accepted);

public:
    MCLIB_API Inventory(int windowId);

    MCLIB_API Slot GetItem(int32_t index) const;
    MCLIB_API const ItemMap& GetItems() const noexcept { return m_Items; }

    const Slot& GetCursorItem() const { return m_Cursor; }

    // Returns item slot index. Returns -1 if none are found.
    MCLIB_API int32_t FindItemById(int32_t itemId) const;

    MCLIB_API bool Contains(int32_t itemId) const;
    MCLIB_API bool Contains(Slot item) const;
    MCLIB_API bool ContainsAtLeast(int32_t itemId, int32_t amount) const;
    MCLIB_API bool ContainsAtLeast(Slot item, int32_t amount) const;

    // Moves an item to the cursor. It will fail if something is already on
    // cursor or if target slot is empty.
    MCLIB_API bool PickUp(core::Connection& conn, int32_t index);
    // Place the current cursor item into a slot.
    // The server may set the new cursor to the item in the target slot.
    MCLIB_API bool Place(core::Connection& conn, int32_t index);

    friend class InventoryManager;
};

class InventoryManager : public protocol::packets::PacketHandler {
private:
    core::Connection* m_Connection;
    std::map<int32_t, std::unique_ptr<Inventory>> m_Inventories;

    void SetSlot(int32_t windowId, int32_t slotIndex, const Slot& slot);

public:
    MCLIB_API InventoryManager(protocol::packets::PacketDispatcher* dispatcher,
                               core::Connection* connection);
    MCLIB_API ~InventoryManager();

    MCLIB_API void HandlePacket(protocol::packets::in::SetSlotPacket* packet);
    MCLIB_API void HandlePacket(
        protocol::packets::in::WindowItemsPacket* packet);
    MCLIB_API void HandlePacket(
        protocol::packets::in::OpenWindowPacket* packet);
    MCLIB_API void HandlePacket(
        protocol::packets::in::ConfirmTransactionPacket* packet);

    MCLIB_API Inventory* GetInventory(int32_t windowId);
    MCLIB_API Inventory* GetPlayerInventory();
};

}  // namespace inventory
}  // namespace mc

#endif
