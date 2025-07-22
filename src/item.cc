#include "item.h"

Item::Item(const Entity::EntityImpl &data, bool autoPickup):
    Entity{data}, autoPickup{autoPickup} {}

char Item::icon() const {
    return 'I';
}
