#include "character.h"
#include <memory>
#include "potion.h"
#include <cmath>

int Character::getATK() const { return atk + deltaAtk; }
int Character::getDEF() const { return def + deltaDef; }
int Character::getHP() const { return hp; }
int Character::getACC() const { return acc; }
int Character::getGold() const { return gold; }
int Character::getDamageDealt() const { return damageDealt; }

void Character::setHP(int new_hp) {hp = new_hp;}
void Character::setATK(int new_atk) {atk = new_atk;}
void Character::setDEF(int new_def) {def = new_def;}
void Character::setACC(int new_acc) {acc = new_acc;}
void Character::setGold(int new_gold) {gold = new_gold;}
void Character::setDamageDealt(int damage) {damageDealt = damage;}

void Character::changeDeltaATK(int deltaDeltaAtk) {
    deltaAtk += deltaDeltaAtk;
}

void Character::changeDeltaDEF(int deltaDeltaDEF) {
    deltaDef += deltaDeltaDEF;
}

void Character::resetDeltaStats() {
    deltaAtk = 0;
    deltaDef = 0;
}

Character::Character(CharacterDefaults d):
    Entity(), atk{d.atk}, def{d.def}, hp{d.hp}, acc{d.acc}, gold{d.gold} {}

void Character::attack(Tile& target) {
    // get information about the entity being attacked
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) {
        this->setDamageDealt(0);
        return;
    } // not a character
    int damage = getDamage(target);
    c->setHP(c->getHP() - damage); // do damage
    this->setDamageDealt(static_cast<int>(damage));
    if (c->getHP() <= 0) {
        this->setGold(this->getGold() + c->getGold());
        target.setEntity(nullptr);
    } // kill if dead
}

int Character::getDamage(Tile& target) {
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) return 0; // not a character, don't do no damage
    int damage = static_cast<int>(ceil((100.0f/(100.0f + static_cast<float>(c->getDEF()))) * static_cast<float>(atk)));
    return damage;
}

