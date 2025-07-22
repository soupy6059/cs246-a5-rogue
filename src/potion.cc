#include "potion.h"

#include "util.h"

Potion::Potion(const Entity::EntityImpl &data):
    Item{data} {}

HealthPotion(const Entity::EntityImpl &data):
    Potion{data} {}

char Potion::icon() const {
    return 'P';
}

char HealthPotion::icon() const {
    return 'H';
}

void Potion::affect(Entity &e) override {
    getCout() << "THE POTION DOES NOTHING!!!!" << endl;
}

void HealthPotion::affect(Entity &e) override {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setHP(character.getHP() + 10);
    }
    catch(const bad_cast &ex) {}
}
