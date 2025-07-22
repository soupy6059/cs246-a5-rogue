#include "enemy.h"
#include "rng.h"
#include <cmath>

void Enemy::attack(Tile& target) {
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) return; // not a character
    int damage = ceil((100/(100 + c->getDEF())) * atk);
    c->setHP(c->getHP() - damage); // do damage
    if (c->getHP() <= 0) {target.setEntity(nullptr);} // kill if dead
}

void Enemy::step() {
    // get a random number
    int i = getRand(0, 8); //gets a number 0 to 7
    // map to direction
    Direction dir;
    switch(i) {
        case 0:
        dir = Direction::NORTH;
        break;
        case 1:
        dir = Direction::NORTHEAST;
        break;
        case 2:
        dir = Direction::EAST;
        break;
        case 3:
        dir = Direction::SOUTHEAST;
        break;
        case 4:
        dir = Direction::SOUTH;
        break;
        case 5:
        dir = Direction::SOUTHWEST;
        break;
        case 6:
        dir = Direction::WEST;
        break;
        case 7:
        dir = Direction::NORTHWEST;
        break;
    }
    //set status
    // notify observers
}