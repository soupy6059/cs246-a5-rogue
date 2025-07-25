#ifndef __game__
#define __game__

#include <array>
#include <memory>
#include <string>

#include "level.h"
#include "races.h"
#include "entity.h"
#include "util.h"
#include "subjectObserver.h"

// note that switch floors means the textDisplay has to observer a new grid

class Game: public Subject, public Observer {
    LevelFactory levelFactory; // "has-a" creator for level
    std::shared_ptr<Player> player; // game needs to set what level a player is on
    static const std::size_t NUMBER_OF_LEVELS = 5;
    std::array<std::unique_ptr<Level>,NUMBER_OF_LEVELS> levels;
    size_t currentLevelIndex = 0;
    bool run = true;
    void updateScan(Level&); // scans topleft across then down for updates
    bool updateLoop(); // main update loop
    public:
    Game(std::string levelFileName = "assets/level-empty.txt", int seed = 0, Race race = Race::SHADE);
    virtual ~Game() = default;

    Level &refCurrentLevel();
    size_t getCurrentLevelIndex();
    std::shared_ptr<Player> getPlayer();

    bool start(); // set up and begin the main update loop
    virtual void notify(Subject&) override;
    void cleanUp(); // detaches observers to avoid leaks
};

#endif
