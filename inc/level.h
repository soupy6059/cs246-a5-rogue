#ifndef __level__
#define __level__

#include <memory>
#include <fstream>
#include <string>
#include "grid.h"
#include "util.h"
#include "player.h"

static const size_t FLOOR_HEIGHT = 25;
static const size_t FLOOR_WIDTH = 79;

class Level {
    std::shared_ptr<Grid> ownedGrid;
    void attachTilesToGrid();
    public:
    Level(size_t,size_t); // idk what the params are
    virtual ~Level() = default;
    Level(Level&&); // enforced by array
    Level(const Level&) = delete;
    Level &operator=(Level&&); // enforced by array, you have to impl
    Level &operator=(const Level&) = delete;

    Grid &getGrid() const;
};

class LevelFactory {
    const std::string file;
    std::vector<std::vector<Vec2>> getRooms(const Level &level);
    public:
    LevelFactory(const std::string &file = "assets/level-empty.txt"); // loads "default.level"
    virtual ~LevelFactory() = default;
    std::unique_ptr<Level> create(std::shared_ptr<Player> player);
};

#endif
