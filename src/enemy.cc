#include "enemy.h"
#include <iostream>
#include "rng.h"
#include "player.h"
#include <cmath>

void Enemy::attack(Tile& target) {
    int hit_target = getRand(0, 2);
    std::cout << "enemy attack rolled: " << hit_target << std::endl;
    if (!hit_target) return;
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) return; // not a character
    float damage = ceil((100/(100 + static_cast<float>(c->getDEF()))) * static_cast<float>(atk));
    std::cout << "damage calced as: " << damage << std::endl;
    c->setHP(c->getHP() - static_cast<int>(damage)); // do damage
    if (c->getHP() <= 0) {target.setEntity(nullptr);} // kill if dead
}

void Enemy::moveNewDir() {
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
    setStatus(Entity::Status{
            .action = Entity::Action::MOVE,
            .data = dir
    });
    // notify observers
    notifyObservers();
}

std::shared_ptr<Tile> Enemy::playerTile(bool &found) {
    // auto observer = getObservers();
    for (auto observer : getObservers()) {
        std::shared_ptr<Tile> myTile = std::dynamic_pointer_cast<Tile>(observer);
        for (auto tileAsObserver : myTile->getObservers()) {
            std::shared_ptr<Tile> neighbourTile = std::dynamic_pointer_cast<Tile>(tileAsObserver);
            if (!neighbourTile) continue;
            std::shared_ptr<Player> thePlayer = std::dynamic_pointer_cast<Player>(neighbourTile->getEntity());
            if (thePlayer) {
                found = true;
                return neighbourTile;
            }
        }
    }
    return nullptr;
}

void Enemy::step() {
    bool canAttack = false;
    std::shared_ptr<Tile> playerLocation = playerTile(canAttack);
    if (canAttack && playerLocation != nullptr) {
        attack(*playerLocation);
    } else {
         moveNewDir();
    }
}

std::string Enemy::icon() const { return "\033[31;1m?\033[0m";}

Enemy::Enemy(CharacterDefaults d): Character{d} {}
