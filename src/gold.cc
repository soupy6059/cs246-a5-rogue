#include "gold.h"

#include <exception>
#include <stdexcept>
#include <string>

#include "player.h"
#include "util.h"
#include "races.h"

using namespace std;

Gold::Gold(int value):
    Item{}, value{value} {}

string Gold::icon() const {
    return "\033[93;1mG\033[0m";
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

DragonHoard::DragonHoard():
    Gold{6} {}

bool DragonHoard::hasDragon() const { return static_cast<bool>(myDragon); } // TODO

void DragonHoard::setDragon(std::shared_ptr<Dragon> newMyDragon) {
    myDragon = newMyDragon;
}

void DragonHoard::mainUpdate() {
    if(myDragon && myDragon->getHP() <= 0) myDragon = nullptr;
    step();
}
