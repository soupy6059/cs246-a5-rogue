#include "character.h"
#include <memory>

int Character::getATK() { return atk; }
int Character::getDEF() { return def; }
int Character::getHP() { return hp; }
int Character::getACC() { return acc; }

void Character::setHP(int new_hp) {hp = new_hp;}
void Character::setATK(int new_atk) {atk = new_atk;}
void Character::setDEF(int new_def) {def = new_def;}
void Character::setACC(int new_acc) {acc = new_acc;}

Character::Character(Entity::EntityImpl ent_info, int atk, int def, int hp, int acc):
    Entity{ent_info}, atk{atk}, def{def}, hp{hp}, acc{acc} {}

void Character::attack(Tile& target) {
    // get information about the entity being attacked
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) return; // not a character
    int damage = atk - c->getDEF();
    c->setHP(c->getHP() - damage); // do damage
    if (c->getHP() <= 0) {target.setEntity(nullptr);} // kill if dead
}

