#ifndef MCLIB_ENTITY_ENTITY_FACTORY_H_
#define MCLIB_ENTITY_ENTITY_FACTORY_H_

#include <mclib/entity/Entity.h>

namespace mc {
namespace entity {

class EntityFactory {
public:
    static Entity* CreateEntity(EntityId id, uint8_t type);
};

}  // namespace entity
}  // namespace mc

#endif
