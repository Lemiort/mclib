#ifndef MCLIB_ENTITY_XPORB_H_
#define MCLIB_ENTITY_XPORB_H_

#include <mclib/entity/Entity.h>

namespace mc {
namespace entity {

class XPOrb : public Entity {
private:
    uint16_t m_Count;

public:
    XPOrb(EntityId eid, protocol::Version protocolVersion)
        : Entity(eid, protocolVersion), m_Count(0) {
        SetType(EntityType::XPOrb);
    }
    XPOrb(EntityId eid, uint16_t count, protocol::Version protocolVersion)
        : Entity(eid, protocolVersion), m_Count(count) {
        SetType(EntityType::XPOrb);
    }

    inline uint16_t GetCount() const noexcept { return m_Count; }
    void SetCount(uint16_t count) { m_Count = count; }
};

}  // namespace entity
}  // namespace mc

#endif
