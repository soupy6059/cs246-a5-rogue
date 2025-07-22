#include "gold.h"

Gold::Gold(const Entity::EntityImpl &data, int value):
    Item{data}, value{value} {}

char Gold::icon() const {
    return 'G';
}

int Gold::getValue() { return value; }

DragonHoard::DragonHoard(const Entity::EntityImpl &data, int value):
    Gold{data, value} {}

bool DragonHoard::hasDragon() const { return false; }
