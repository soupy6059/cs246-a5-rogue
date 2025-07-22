#include "item.h"

Item::Item(const Entity::EntityImpl &data):
    Entity{data} {}

char Item::icon() const {
    return 'I';
}
