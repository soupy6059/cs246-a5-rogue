#include "game.h"

#include <iostream>

#include "player.h"
#include "util.h"
#include "gold.h"
#include "rng.h"
#include "races.h"

using namespace std;

Game::Game(string levelFileName, int seed, Race race):
    levelFactory{levelFileName},
    player{std::dynamic_pointer_cast<Player>(makeEntityWithRace(race))},
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

shared_ptr<Player> Game::getPlayer() {
    return player;
}

size_t Game::getCurrentLevelIndex() {
    return currentLevelIndex;
}

bool Game::updateLoop() {
    while(run) {
        updateScan(refCurrentLevel());
        if (refCurrentLevel().isPlayerOnStairs()) {
            refCurrentLevel().getGrid()
                .at(refCurrentLevel().getStairsLocation())
                ->setEntity(nullptr);
            ++currentLevelIndex;
            if (currentLevelIndex == NUMBER_OF_LEVELS) {
                cout << "You Win! Score: " << player->getScore() << endl;
                return false;
            }
            else refCurrentLevel().setActiveLevel(player);
        } else if (player->getStatus().action == Entity::Action::QUIT) {
            return false;
        } else if (player->getStatus().action == Entity::Action::RESTART) {
            return true;
        } else if (player->getStatus().action == Entity::Action::PLAYER_DEATH) {
            cout << "You Died" << endl;
            return false;
        }
    }
    return false;
}

void Game::notify(Subject &whoFrom) {
    try { dynamic_cast<Player&>(whoFrom); }
    catch(...) { return; }
    if(player->getStatus().action != Entity::Action::PRINT_LEVEL) return;
    notifyObservers();
}

Level &Game::refCurrentLevel() {
    return *levels[currentLevelIndex];
}

// basically our main() function
//
// mostly temporary for now
bool Game::start() {
    Enemy::setCanMove(true);
    Level &mainLevel {*levels[0]};
    mainLevel.setActiveLevel(player);
    // static const Vec2 location {3,3};
    // mainLevel.getGrid().at(location)->setEntity(player);
    // mainLevel.getGrid().at(location)->getEntity()->attach(
    //     mainLevel.getGrid().at(location)
    // );

    bool playAgain = updateLoop();
    cleanUp();
    return playAgain;
}

void Game::cleanUp() {
    detachAll();
    player->detachAll();
    for (int unsigned i = 0; i < NUMBER_OF_LEVELS; ++i) {
        for (auto &v : levels[i]->getGrid().getTheGrid()) {
            for (auto &t : v) {
                t->detachAll();
                if (t->getEntity()) t->getEntity()->detachAll();
            }
        }
    }
}
