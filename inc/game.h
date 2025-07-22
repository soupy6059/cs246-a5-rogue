#ifndef __game__
#define __game__

#include <array>
#include <memory>
#include <string>

#include "level.h"
#include "entity.h"

// note that switch floors means the textDisplay has to observer a new grid

class Game {
    LevelFactory levelFactory;
    std::shared_ptr<Player> player;
    static const std::size_t NUMBER_OF_LEVELS = 5;
    std::array<std::unique_ptr<Level>,NUMBER_OF_LEVELS> levels;
    public:
    Game(std::string levelFileName = "assets/level-empty.txt", int seed = 0);
    virtual ~Game() = default;
    void start();
};

#endif
