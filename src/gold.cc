#include "gold.h"

#include <exception>
#include <stdexcept>
#include <string>

#include "player.h"

using namespace std;

Gold::Gold(const Entity::EntityImpl &data, int value):
    Item{data}, value{value} {}

char Gold::icon() const {
    return 'G';
}

int Gold::getValue() { return value; }

void Gold::step() {}
void Gold::affect(Entity& e) {
    try {
        Player &player {dynamic_cast<Player&>(e)};
        player.setGold(player.getGold() + this->getValue());
    }
    catch(const bad_cast &ex) {}
}

DragonHoard::DragonHoard(const Entity::EntityImpl &data, int value):
    Gold{data, value} {}

bool DragonHoard::hasDragon() const { return false; } // TODO

