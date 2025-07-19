#ifndef __game__
#define __game__

#include <array>
#include <memory>

#include "level.h"
#include "entity.h"

class Game {
    LevelFactory levelFactory;
    std::shared_ptr<Entity> player;
    static const std::size_t NUMBER_OF_LEVELS = 5;
    std::array<std::unique_ptr<Level>,NUMBER_OF_LEVELS> levels;
    public:
    Game();
    virtual ~Game() = default;
    void start();
};

#endif
