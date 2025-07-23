#include "game.h"

#include <iostream>

#include "player.h"
#include "gold.h"
#include "rng.h"

using namespace std;

Game::Game(string levelFileName, int seed):
    levelFactory{levelFileName},
    player{make_shared<Player>(0, 0, 0, 0)},
    levels{nullptr} {
    initRand(seed);
    for(size_t i{0}; i < levels.size(); ++i) {
        levels.at(i) = levelFactory.create();
    }
}

void Game::updateScan(Level &level) {
    Grid &grid = level.getGrid();
    for(auto &tiles: grid.getTheGrid()) {
        for(auto &tilePtr: tiles) {
            if(auto entityPtr {tilePtr->getEntity()}; entityPtr) {
                if(entityPtr->getDoubleRisk()) entityPtr->setDoubleRisk(false);
                else entityPtr->update();
            }
        }
    }
}

void Game::updateLoop() {
    while(run) {
        levels[currentLevelIndex]->getGrid().print(cout);
        updateScan(*levels[currentLevelIndex]);
    }
}

// basically our main() function
//
// mostly temporary for now
void Game::start() {
    Level &mainLevel {*levels[0]};
    mainLevel.setActiveLevel(player);
    // static const Vec2 location {3,3};
    // mainLevel.getGrid().at(location)->setEntity(player);
    // mainLevel.getGrid().at(location)->getEntity()->attach(
    //     mainLevel.getGrid().at(location)
    // );

    static const Vec2 coinLocal {5,5};
    mainLevel.getGrid().at(coinLocal)->setEntity(make_shared<Gold>(2));
    mainLevel.getGrid().at(coinLocal)->getEntity()->attach(
        mainLevel.getGrid().at(coinLocal)
    );
    updateLoop();
}
