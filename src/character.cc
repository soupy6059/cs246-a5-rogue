#include "character.h"
#include <memory>
#include "potion.h"
#include <cmath>

int Character::getATK() { return atk; }
int Character::getDEF() { return def; }
int Character::getHP() { return hp; }
int Character::getACC() { return acc; }
int Character::getGold() { return gold; }

void Character::setHP(int new_hp) {hp = new_hp;}
void Character::setATK(int new_atk) {atk = new_atk;}
void Character::setDEF(int new_def) {def = new_def;}
void Character::setACC(int new_acc) {acc = new_acc;}
void Character::setGold(int new_gold) {gold = new_gold;}

Character::Character(CharacterDefaults d):
    Entity(), atk{d.atk}, def{d.def}, hp{d.hp}, acc{d.acc}, gold{d.gold} {}

void Character::attack(Tile& target) {
    // get information about the entity being attacked
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) return; // not a character
    int damage = ceil((100/(100 + c->getDEF())) * atk);
    c->setHP(c->getHP() - damage); // do damage
    if (c->getHP() <= 0) {target.setEntity(nullptr);} // kill if dead
}

