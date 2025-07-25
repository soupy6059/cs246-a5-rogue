#include "enemy.h"
#include "rng.h"
#include "player.h"
#include <cmath>

bool Enemy::canMove = true;

bool Enemy::canItMove() {return canMove;}

void Enemy::attack(Tile& target) {
    int hit_target = getRand(0, 2);
    if (!hit_target) {
        this->setDamageDealt(MISSED_ATK_DMG);
        return;
    }
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    if (!c) return; // not a character
    float damage = ceil((100/(100 + static_cast<float>(c->getDEF()))) * static_cast<float>(atk));
    c->setHP(c->getHP() - static_cast<int>(damage)); // do damage
    this->setDamageDealt(static_cast<int>(damage));
    if (c->getHP() <= 0) {
        target.setEntity(nullptr);
    } // kill if dead
}

void Enemy::moveNewDir() {
        // get a random number
    int i = getRand(0, 8); //gets a number 0 to 7
    // map to direction
    Direction dir = Direction::CENTER;
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
    } else if (canMove) {
         moveNewDir();
    }
}

std::string Enemy::icon() const { return "\033[31;1m?\033[0m";}

Enemy::Enemy(CharacterDefaults d): Character{d} {}

void Enemy::toggleCanMove() {canMove = !canMove;}
void Enemy::setCanMove(bool canMove) {
    Enemy::canMove = canMove;
}

void Enemy::setHP(int new_hp) {
    if (new_hp < 0) { 
        hp = 0;
    } else {
        hp = new_hp;
    }
}
