#include <mclib/core/ClientSettings.h>

namespace mc {
namespace core {

constexpr auto FullSkin =
    (uint8_t)((uint8_t)SkinPart::Cape | (uint8_t)SkinPart::Jacket | (uint8_t)SkinPart::LeftSleeve |
         (uint8_t)SkinPart::RightSleeve | (uint8_t)SkinPart::LeftPants |
         (uint8_t)SkinPart::RightPants | (uint8_t)SkinPart::Hat);

ClientSettings::ClientSettings()
    : m_Locale(L"en_GB"),
      m_ChatMode(ChatMode::Enabled),
      m_MainHand(MainHand::Right),
      m_ViewDistance(16),
      m_SkinParts(FullSkin),
      m_ChatColors(true) {}

ClientSettings& ClientSettings::SetLocale(const std::wstring& locale) {
    m_Locale = locale;
    return *this;
}

ClientSettings& ClientSettings::SetChatMode(ChatMode mode) noexcept {
    m_ChatMode = mode;
    return *this;
}

ClientSettings& ClientSettings::SetMainHand(MainHand main) noexcept {
    m_MainHand = main;
    return *this;
}

ClientSettings& ClientSettings::SetViewDistance(uint8_t distance) noexcept {
    m_ViewDistance = distance;
    return *this;
}

ClientSettings& ClientSettings::SetViewDistance(int32_t distance) noexcept {
    this->SetViewDistance((uint8_t)distance);
    return *this;
}

ClientSettings& ClientSettings::SetSkinParts(uint8_t parts) noexcept {
    m_SkinParts = parts;
    return *this;
}
ClientSettings& ClientSettings::SetChatColors(bool chatColors) noexcept {
    m_ChatColors = chatColors;
    return *this;
}

ClientSettings& ClientSettings::SetSkinPart(SkinPart part,
                                            bool display) noexcept {
    if (display) {
        m_SkinParts |= (uint8_t)part;
    } else {
        m_SkinParts &= ~(uint8_t)part;
    }
    return *this;
}

}  // namespace core
}  // namespace mc
