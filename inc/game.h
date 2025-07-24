#ifndef __game__
#define __game__

#include <array>
#include <memory>
#include <string>

#include "level.h"
#include "entity.h"
#include "util.h"
#include "subjectObserver.h"

// note that switch floors means the textDisplay has to observer a new grid

class Game: public Subject, public Observer {
    LevelFactory levelFactory;
    std::shared_ptr<Player> player;
    static const std::size_t NUMBER_OF_LEVELS = 5;
    std::array<std::unique_ptr<Level>,NUMBER_OF_LEVELS> levels;
    size_t currentLevelIndex = 0;
    bool run = true;
    void updateScan(Level&);
    void updateLoop();
    public:
    Game(std::string levelFileName = "assets/level-empty.txt", int seed = 0);
    virtual ~Game() = default;
    void start();
    Level &refCurrentLevel();
    size_t getCurrentLevelIndex();
    std::shared_ptr<Player> getPlayer();
    virtual void notify(Subject&) override;

    void cleanUp();
};

#endif
