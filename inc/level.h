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

static const unsigned int MAX_POTIONS = 10;
static const unsigned int MAX_ENEMIES = 20;
static const unsigned int MAX_GOLD = 10;


class Level {
    std::shared_ptr<Grid> ownedGrid;
    Vec2 playerSpawnLocation;
    void attachTilesToGrid();
    public:
    Level(size_t,size_t); // idk what the params are
    virtual ~Level() = default;
    Level(Level&&); // enforced by array
    Level(const Level&) = delete;
    Level &operator=(Level&&); // enforced by array, you have to impl
    Level &operator=(const Level&) = delete;

    Grid &getGrid() const;

    void setSpawnLocation(Vec2 loc);

    void spawnAt(const std::shared_ptr<Entity> entity, Vec2 loc);

    void setActiveLevel(const std::shared_ptr<Player> player);
};

class LevelFactory {
    const std::string file;
    std::vector<std::vector<Vec2>> getRooms(const Level &level);
    public:
    LevelFactory(const std::string &file = "assets/level-empty.txt"); // loads "default.level"
    virtual ~LevelFactory() = default;
    std::unique_ptr<Level> create();
};

#endif
