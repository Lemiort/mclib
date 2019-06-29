#ifndef MCLIB_CORE_CLIENTSETTINGS_H
#define MCLIB_CORE_CLIENTSETTINGS_H

#include <mclib/common/Types.h>
#include <mclib/mclib.h>
#include <string>

namespace mc {
namespace core {

class ClientSettings {
private:
    std::wstring m_Locale;
    ChatMode m_ChatMode;
    MainHand m_MainHand;
    uint8_t m_ViewDistance;
    uint8_t m_SkinParts;
    bool m_ChatColors;

public:
    MCLIB_API ClientSettings();

    MCLIB_API ClientSettings(const ClientSettings& rhs) = default;
    MCLIB_API ClientSettings& operator=(const ClientSettings& rhs) = default;
    MCLIB_API ClientSettings(ClientSettings&& rhs) = default;
    MCLIB_API ClientSettings& operator=(ClientSettings&& rhs) = default;

    MCLIB_API ClientSettings& SetLocale(const std::wstring& locale);
    MCLIB_API ClientSettings& SetChatMode(ChatMode mode) noexcept;
    MCLIB_API ClientSettings& SetMainHand(MainHand main) noexcept;
    MCLIB_API ClientSettings& SetViewDistance(uint8_t distance) noexcept;
    MCLIB_API ClientSettings& SetViewDistance(int32_t distance) noexcept;
    MCLIB_API ClientSettings& SetSkinParts(uint8_t parts) noexcept;
    MCLIB_API ClientSettings& SetChatColors(bool chatColors) noexcept;

    MCLIB_API ClientSettings& SetSkinPart(SkinPart part, bool display) noexcept;

    MCLIB_API inline const std::wstring& GetLocale() const noexcept {
        return m_Locale;
    }
    MCLIB_API inline ChatMode GetChatMode() const noexcept {
        return m_ChatMode;
    }
    MCLIB_API inline MainHand GetMainHand() const noexcept {
        return m_MainHand;
    }
    MCLIB_API inline uint8_t GetViewDistance() const noexcept {
        return m_ViewDistance;
    }
    MCLIB_API inline uint8_t GetSkinParts() const noexcept { return m_SkinParts; }
    MCLIB_API inline bool GetChatColors() const noexcept {
        return m_ChatColors;
    }
};

}  // namespace core
}  // namespace mc

#endif
