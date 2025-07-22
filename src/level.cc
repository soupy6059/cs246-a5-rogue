#include "level.h"
#include "grid.h"
#include "tile.h"
#include "rng.h"


#include <memory>
#include <utility>
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

Level::Level(size_t rowCount, size_t colCount):
    ownedGrid{make_unique<Grid>(rowCount,colCount)},
    playerSpawnLocation{0,0} {
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

void Level::setSpawnLocation(Vec2 loc) {
    playerSpawnLocation = loc;
}

void Level::spawnAt(const shared_ptr<Entity> entity, Vec2 loc) {
    ownedGrid->at(loc)->setEntity(entity);
    ownedGrid->at(loc)->getEntity()->attach(
        ownedGrid->at(loc)
    );
}

void Level::setActiveLevel(const shared_ptr<Player> player) {
    spawnAt(player, playerSpawnLocation);
}

LevelFactory::LevelFactory(const string &file):
    file{file} {}

unique_ptr<Level> LevelFactory::create() {
    ifstream in{file};
    if (!in) throw logic_error("bad file: file not found");
    auto level = make_unique<Level>(FLOOR_HEIGHT, FLOOR_WIDTH);
    auto theGrid = level->getGrid().getTheGrid();

    for (size_t r = 0; r < FLOOR_HEIGHT; ++r) {
        string line;
        if (!getline(in, line)) throw logic_error("bad file: not enough lines");
        if (line.size() < FLOOR_WIDTH) throw logic_error("bad file: line too short");
        for (size_t c = 0; c < FLOOR_WIDTH; ++c) {
            theGrid[r][c]->setType(fromChar(line[c]));
        }
    }

    auto rooms = getRooms(*level);

    size_t playerRoom = getRand(0,rooms.size());
    level->setSpawnLocation(rooms[playerRoom][getRand(0,rooms[playerRoom].size())]);

    size_t stairsRoom = getRand(0,rooms.size());
    if (stairsRoom == playerRoom && rooms.size() > 1)
        while (stairsRoom == playerRoom) 
            stairsRoom = getRand(0,rooms.size());

    Vec2 stairsLocation = rooms[stairsRoom][getRand(0,rooms[stairsRoom].size())];

    theGrid[stairsLocation.x][stairsLocation.y]->setType(Tile::TileType::STAIR);

    // TODO: Generate items and entities

    return level;
}

vector<vector<Vec2>> LevelFactory::getRooms(const Level &level) { // LeetCode 200
    vector<vector<bool>> visited(FLOOR_HEIGHT, vector(FLOOR_WIDTH, false));
    vector<vector<Vec2>> rooms{};

    auto grid = level.getGrid().viewTheGrid();

    for (size_t r = 0; r < FLOOR_HEIGHT; ++r) {
        for (size_t c = 0; c < FLOOR_WIDTH; ++c) {
            if (visited[r][c] || !grid[r][c]->isFloor()) continue;

            rooms.push_back(vector<Vec2>{});
            rooms.back().emplace_back(r,c);
            visited[r][c] = true;
            for (unsigned int i = 0; i < rooms.back().size(); ++i) {
                Vec2 pos = rooms.back()[i];
                if (pos.x > 0 && !visited[pos.x-1][pos.y]
                    && grid[pos.x-1][pos.y]->isFloor()) {
                    rooms.back().push_back(Vec2{pos.x-1,pos.y});
                    visited[pos.x-1][pos.y] = true;
                }
                if (pos.x < (int)FLOOR_HEIGHT-1 && !visited[pos.x+1][pos.y]
                    && grid[pos.x+1][pos.y]->isFloor()) {
                    rooms.back().push_back(Vec2{pos.x+1,pos.y});
                    visited[pos.x+1][pos.y] = true;
                }
                if (pos.y > 0 && !visited[pos.x][pos.y-1]
                    && grid[pos.x][pos.y-1]->isFloor()) {
                    rooms.back().push_back(Vec2{pos.x,pos.y-1});
                    visited[pos.x][pos.y-1] = true;
                }
                if (pos.y < (int)FLOOR_WIDTH-1 && !visited[pos.x][pos.y+1]
                    && grid[pos.x][pos.y+1]->isFloor()) {
                    rooms.back().push_back(Vec2{pos.x,pos.y+1});
                    visited[pos.x][pos.y+1] = true;
                }
            }
        }
    }

    return rooms;
}
