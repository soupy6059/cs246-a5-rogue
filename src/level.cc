#include "level.h"
#include "grid.h"
#include "tile.h"

#include <utility>
#include <exception>
#include <stdexcept>

using namespace std;

Level::Level(size_t rowCount, size_t colCount):
    ownedGrid{make_unique<Grid>(rowCount,colCount)} {
    attachTilesToGrid();
}

Level::Level(Level &&other):
    ownedGrid{move(other.ownedGrid)} {}

// Level::Level(const Level &other):
//     ownedGrid{make_unique<Grid>(*other.ownedGrid)} {}

Level &Level::operator=(Level &&other) {
    swap(ownedGrid, other.ownedGrid);
    return *this;
}

void Level::attachTilesToGrid() {
    for(auto &row: getGrid().getTheGrid()) {
        for(auto &tile: row) {
            tile->attach(ownedGrid);
        }
    }
}

// Level &Level::operator=(const Level &other) {
//     return *this = Level{other};
// }

Grid &Level::getGrid() const {
    return *ownedGrid;
}

LevelFactory::LevelFactory():
    leveldata{make_unique<ifstream>(ifstream{"level-empty.txt"})} {}

void LevelFactory::load(string file) {
    leveldata = make_unique<ifstream>(ifstream{file});
}

unique_ptr<Level> LevelFactory::create() {
    auto level = make_unique<Level>(Level::FLOOR_HEIGHT, Level::FLOOR_WIDTH);
    auto theGrid = level->getGrid().getTheGrid();

    for (int r = 0; r < Level::FLOOR_HEIGHT; ++r) {
        string line;
        if (!getline(*leveldata, line)) throw logic_error("bad file");
        if (line.size() < Level::FLOOR_WIDTH) throw logic_error("bad file");
        for (int c = 0; c < Level::FLOOR_WIDTH; ++c) {
            theGrid[r][c]->setType(fromChar(line[c]));
        }
    }

    // TODO: Generate items and entities

    return level;
}

