#include "game.h"

#include <iostream>

#include "player.h"
#include "gold.h"
#include "rng.h"

using namespace std;

Game::Game(int seed):
    levelFactory{},
    player{make_shared<Player>(
        Entity::EntityImpl{
            .status = Entity::Status {
                .action = Entity::Action::NOTHING,
                .DUMMY = true,
            }
        }
    )},
    levels{nullptr} {
    initRand(seed);
    for(size_t i{0}; i < levels.size(); ++i) {
        levels.at(i) = levelFactory.create(player);
    }
}

// basically our main() function
//
// mostly temporary for now
void Game::start() {
    Level &mainLevel {*levels[0]};
    static const Vec2 location {3,3};
    mainLevel.getGrid().at(location)->setEntity(player);
    mainLevel.getGrid().at(location)->getEntity()->attach(
        mainLevel.getGrid().at(location)
    );

    static const Vec2 coinLocal {5,5};
    mainLevel.getGrid().at(coinLocal)->setEntity(make_shared<Gold>(
        Entity::EntityImpl{
            .status = Entity::Status {
                .action = Entity::Action::NOTHING,
                .DUMMY = true,
            }
        },
        2 // value
    ));
    mainLevel.getGrid().at(coinLocal)->getEntity()->attach(
        mainLevel.getGrid().at(coinLocal)
    );
    
    while(true) {
        mainLevel.getGrid().print(cout);
        player->update();
        getCout() << dynamic_pointer_cast<Player>(player)->getGold() << endl;
    }
}
