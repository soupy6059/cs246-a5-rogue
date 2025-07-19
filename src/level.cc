#include "level.h"

#include <utility>
#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

Level::Level(size_t rowCount, size_t colCount):
    ownedGrid{make_unique<Grid>(rowCount,colCount)} {}

Level::Level(Level &&other):
    ownedGrid{move(other.ownedGrid)} {}

// Level::Level(const Level &other):
//     ownedGrid{make_unique<Grid>(*other.ownedGrid)} {}

Level &Level::operator=(Level &&other) {
    swap(ownedGrid, other.ownedGrid);
    return *this;
}

// Level &Level::operator=(const Level &other) {
//     return *this = Level{other};
// }

Grid &Level::getGrid() const {
    return *ownedGrid;
}

LevelFactory::LevelFactory() {}

void LevelFactory::load(string file [[maybe_unused]]) {
    throw logic_error{"todo"};
}

unique_ptr<Level> LevelFactory::create() {
    return make_unique<Level>(10,10);
}

