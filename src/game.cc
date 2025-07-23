#include "game.h"

#include <iostream>

#include "player.h"
#include "util.h"
#include "gold.h"
#include "rng.h"
#include "races.h"

using namespace std;

Game::Game(string levelFileName, int seed):
    levelFactory{levelFileName},
    player{make_shared<Player>(getCharDefs(Race::SHADE))},
    levels{nullptr} {
    initRand(seed);
    for(size_t i{0}; i < levels.size(); ++i) {
        levels.at(i) = levelFactory.create();
    }
}

void Game::notify(Subject &whoFrom) {
    try {
        dynamic_cast<Player&>(whoFrom);
    } catch(...) { return; }
    if(player->getStatus().action != Entity::Action::CHANGE_LEVEL) return;

    ++currentLevelIndex; // 0 -> 1
    cout << "new level index: " << currentLevelIndex << endl;
    refCurrentLevel().setActiveLevel(player);
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

shared_ptr<Player> Game::getPlayer() {
    return player;
}

size_t Game::getCurrentLevelIndex() {
    return currentLevelIndex;
}

void Game::updateLoop() {
    while(run) {
        notifyObservers();
        updateScan(refCurrentLevel());
    }
}

Level &Game::refCurrentLevel() {
    return *levels[currentLevelIndex];
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
