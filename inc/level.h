#ifndef __level__
#define __level__

#include <memory>
#include <fstream>
#include <string>
#include "grid.h"

static const size_t FLOOR_HEIGHT = 30;
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
    std::unique_ptr<std::istream> leveldata;
    public:
    LevelFactory(); // loads "default.level"
    virtual ~LevelFactory() = default;
    void load(std::string file); // reloads "file"
    std::unique_ptr<Level> create();
};

#endif
