#include "gold.h"

#include <exception>
#include <stdexcept>
#include <string>

#include "player.h"
#include "util.h"

using namespace std;

Gold::Gold(int value):
    Item{}, value{value} {}

char Gold::icon() const {
    return 'G';
}

int Gold::getValue() { return value; }

        bool doubleRisk;
void Gold::step() {}
void Gold::affect(Entity& e) {
    try {
        Player &player {dynamic_cast<Player&>(e)};
        player.setGold(player.getGold() + this->getValue());
    }
    catch(const bad_cast &ex) {}
}

DragonHoard::DragonHoard(int value):
    Gold{value} {}

bool DragonHoard::hasDragon() const { return false; } // TODO

