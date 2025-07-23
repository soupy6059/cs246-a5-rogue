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

void Gold::step() {}

void Gold::affect(Entity& e) {
    try {
        Player &player {dynamic_cast<Player&>(e)};
        player.setGold(player.getGold() + this->getValue());
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

DragonHoard::DragonHoard(int value):
    Gold{value} {}

bool DragonHoard::hasDragon() const { return false; } // TODO

