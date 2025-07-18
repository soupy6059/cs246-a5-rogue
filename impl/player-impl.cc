module player;

import <iostream>;

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
                .direction = Direction::NORTH,
            });
            break;
        case 's':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .direction = Direction::SOUTH,
            });
            break;
        case 'a':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .direction = Direction::WEST,
            });
            break;
        case 'd':
            setStatus(Entity::Status{
                .action = Entity::Action::MOVE,
                .direction = Direction::EAST,
            });
            break;
        default:
            badRead = true;
            break;
        }
    }
    notifyObservers();
}
