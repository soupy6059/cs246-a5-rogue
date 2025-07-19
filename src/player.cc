#include "player.h"

#include <iostream>

using namespace std;

Player::Player(const Entity::EntityImpl &data):
    Entity{data} {}

void Player::step() {
    char input;
    cin >> input;
    for(bool badRead = false; badRead; badRead = false) {
        switch(input) {
        case 'w':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .dir = Direction::NORTH,
            });
            break;
        case 's':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .dir = Direction::SOUTH,
            });
            break;
        case 'a':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .dir = Direction::WEST,
            });
            break;
        case 'd':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .dir = Direction::EAST,
            });
            break;
        default:
            badRead = true;
            break;
        }
    }
    notifyObservers();
}
