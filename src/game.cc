#include "game.h"
#include "player.h"

#include <iostream>

using namespace std;

Game::Game():
    levelFactory{},
    player{nullptr},
    levels{nullptr} {
    for(size_t i{0}; i < levels.size(); ++i) {
        levels.at(i) = levelFactory.create();
    }
}

// basically our main() function
//
// mostly temporary for now
void Game::start() {
    Level &mainLevel {*levels[0]};
    static const Vec2 location {0,0};
    mainLevel.getGrid().at(location)->setEntity(make_shared<Player>(
        Entity::EntityImpl{
            .stats{0},
            .status = Entity::Status {
                .action = Entity::Action::NOTHING,
                .dir = Direction::CENTER,
            }
        }
    ));
    player = mainLevel.getGrid().at(location)->getEntity();
    mainLevel.getGrid().at(location)->getEntity()->attach(
        mainLevel.getGrid().at(location)
    );
      
    
    while(true) {
        mainLevel.getGrid().print(cout);
        player->update();
    }
}
