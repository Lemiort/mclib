#ifndef MCLIB_PROTOCOL_PROTOCOL_H_
#define MCLIB_PROTOCOL_PROTOCOL_H_

#include <mclib/protocol/ProtocolState.h>
#include <mclib/protocol/packets/Packet.h>
#include <string>
#include <unordered_map>

namespace mc {
namespace protocol {

using PacketCreator = packets::InboundPacket* (*)();
using PacketMap = std::unordered_map<int32_t, int32_t>;

class UnsupportedPacketException : public std::exception {
private:
    std::string m_ErrorMessage;

public:
    UnsupportedPacketException(const std::string& message)
        : m_ErrorMessage(message) {}

    virtual const char* what() const noexcept { return m_ErrorMessage.c_str(); }
};

class Protocol {
public:
    typedef std::unordered_map<State, PacketMap> StateMap;

protected:
    StateMap m_InboundMap;
    Version m_Version;

public:
    Protocol(Version version, StateMap inbound)
        : m_InboundMap(inbound), m_Version(version) {}

    virtual ~Protocol() {}

    virtual Version GetVersion() const noexcept { return m_Version; }

    // Creates an inbound packet from state and packet id
    virtual packets::InboundPacket* CreateInboundPacket(State state, int32_t id);

    // Convert the protocol id into a protocol agnostic id.
    // This is used as the dispatching id.
    bool GetAgnosticId(State state, int32_t protocolId, int32_t& agnosticId);

    // Handshake
    virtual int32_t GetPacketId(packets::out::HandshakePacket) { return 0x00; }

    // Login
    virtual int32_t GetPacketId(packets::out::LoginStartPacket) { return 0x00; }
    virtual int32_t GetPacketId(packets::out::EncryptionResponsePacket) {
        return 0x01;
    }

    // Status
    virtual int32_t GetPacketId(packets::out::status::RequestPacket) {
        return 0x00;
    }
    virtual int32_t GetPacketId(packets::out::status::PingPacket) { return 0x01; }

    // Play
    virtual int32_t GetPacketId(packets::out::TeleportConfirmPacket) {
        return 0x00;
    }
    virtual int32_t GetPacketId(packets::out::TabCompletePacket) { return 0x01; }
    virtual int32_t GetPacketId(packets::out::ChatPacket) { return 0x02; }
    virtual int32_t GetPacketId(packets::out::ClientStatusPacket) { return 0x03; }
    virtual int32_t GetPacketId(packets::out::ClientSettingsPacket) { return 0x04; }
    virtual int32_t GetPacketId(packets::out::ConfirmTransactionPacket) {
        return 0x05;
    }
    virtual int32_t GetPacketId(packets::out::EnchantItemPacket) { return 0x06; }
    virtual int32_t GetPacketId(packets::out::ClickWindowPacket) { return 0x07; }
    virtual int32_t GetPacketId(packets::out::CloseWindowPacket) { return 0x08; }
    virtual int32_t GetPacketId(packets::out::PluginMessagePacket) { return 0x09; }
    virtual int32_t GetPacketId(packets::out::UseEntityPacket) { return 0x0A; }
    virtual int32_t GetPacketId(packets::out::KeepAlivePacket) { return 0x0B; }
    virtual int32_t GetPacketId(packets::out::PlayerPositionPacket) { return 0x0C; }
    virtual int32_t GetPacketId(packets::out::PlayerPositionAndLookPacket) {
        return 0x0D;
    }
    virtual int32_t GetPacketId(packets::out::PlayerLookPacket) { return 0x0E; }
    virtual int32_t GetPacketId(packets::out::PlayerPacket) { return 0x0F; }
    virtual int32_t GetPacketId(packets::out::VehicleMovePacket) { return 0x10; }
    virtual int32_t GetPacketId(packets::out::SteerBoatPacket) { return 0x11; }
    virtual int32_t GetPacketId(packets::out::PlayerAbilitiesPacket) {
        return 0x12;
    }
    virtual int32_t GetPacketId(packets::out::PlayerDiggingPacket) { return 0x13; }
    virtual int32_t GetPacketId(packets::out::EntityActionPacket) { return 0x14; }
    virtual int32_t GetPacketId(packets::out::SteerVehiclePacket) { return 0x15; }
    virtual int32_t GetPacketId(packets::out::ResourcePackStatusPacket) {
        return 0x16;
    }
    virtual int32_t GetPacketId(packets::out::HeldItemChangePacket) { return 0x17; }
    virtual int32_t GetPacketId(packets::out::CreativeInventoryActionPacket) {
        return 0x18;
    }
    virtual int32_t GetPacketId(packets::out::UpdateSignPacket) { return 0x19; }
    virtual int32_t GetPacketId(packets::out::AnimationPacket) { return 0x1A; }
    virtual int32_t GetPacketId(packets::out::SpectatePacket) { return 0x1B; }
    virtual int32_t GetPacketId(packets::out::PlayerBlockPlacementPacket) {
        return 0x1C;
    }
    virtual int32_t GetPacketId(packets::out::UseItemPacket) { return 0x1D; }

    virtual int32_t GetPacketId(packets::out::PrepareCraftingGridPacket) {
        throw UnsupportedPacketException(
            "PrepareCraftingGridPacket requires protocol 1.12.0");
    }
    virtual int32_t GetPacketId(packets::out::CraftingBookDataPacket) {
        throw UnsupportedPacketException(
            "CraftingBookDataPacket requires protocol 1.12.0");
    }
    virtual int32_t GetPacketId(packets::out::AdvancementTabPacket) {
        throw UnsupportedPacketException(
            "AdvancementTabPacket requires protocol 1.12.0");
    }

    virtual int32_t GetPacketId(packets::out::CraftRecipeRequestPacket) {
        throw UnsupportedPacketException(
            "CraftRecipeRequestPacket requires protocol 1.12.1");
    }

    static Protocol& GetProtocol(Version version);
};

}  // namespace protocol
}  // namespace mc

#endif
