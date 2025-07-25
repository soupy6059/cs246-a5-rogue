#include "level.h"
#include "grid.h"
#include "tile.h"
#include "rng.h"
#include "potion.h"
#include "races.h"
#include "util.h"


#include <iterator>
#include <memory>
#include <utility>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cassert>

using namespace std;

Level::Level(size_t rowCount, size_t colCount):
    ownedGrid{make_unique<Grid>(rowCount,colCount)},
    playerSpawnLocation{-1,-1},
    stairsLocation{-1,-1} {
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

const Vec2 &Level::getSpawnLocation() const {
    return playerSpawnLocation;
}

void Level::setSpawnLocation(Vec2 loc) {
    playerSpawnLocation = loc;
}

const Vec2 &Level::getStairsLocation() const {
    return stairsLocation;
}

void Level::setStairsLocation(Vec2 loc) {
    stairsLocation = loc;
}

bool Level::isPlayerOnStairs() const {
    return static_cast<bool>(dynamic_pointer_cast<Player>(ownedGrid->at(stairsLocation)->getEntity()));
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

// Helper methods for LevelFactory (implemented below):
static Vec2 getNextSpawnLocation(vector<vector<Vec2>> &rooms);
static Potion::PotionType randomPotionType();
static shared_ptr<Gold> randomGoldType();
static Race randomEnemyType();
static shared_ptr<Entity> charToLootPtr(char c);
static shared_ptr<Entity> charToEnemyPtr(char c);

LevelFactory::LevelFactory(const string &file):
    file{file} {}


unique_ptr<Level> LevelFactory::create() {
    ifstream in{file};
    if (!in) throw logic_error("bad file: file not found");
    auto level = make_unique<Level>(FLOOR_HEIGHT, FLOOR_WIDTH);
    auto theGrid = level->getGrid().getTheGrid();

    unsigned int goldCount = 0, potionCount = 0, enemyCount = 0;

    for (unsigned int r = 0; r < FLOOR_HEIGHT; ++r) {
        string line;
        if (!getline(in, line)) throw logic_error("bad file: not enough lines");
        if (line.size() < FLOOR_WIDTH) throw logic_error("bad file: line too short");
        for (unsigned int c = 0; c < FLOOR_WIDTH; ++c) {
            // Todo: spawn entities from characters in file
            theGrid[r][c]->setType(fromChar(line[c]));
            if (line[c] == '@') level->setSpawnLocation(Vec2{(int)r,(int)c});
            else if (line[c] == '\\') {
                level->setStairsLocation(Vec2{(int)r,(int)c});
                level->getGrid().at(level->getStairsLocation())->setType(Tile::TileType::STAIR);
            } else if (line[c] >= '0' && line[c] <= '9') {
                level->spawnAt(charToLootPtr(line[c]), Vec2{(int)r,(int)c});
                if (line[c] <= '5') ++potionCount;
                else ++goldCount;
            } else if (auto p = charToEnemyPtr(line[c])) {
                level->spawnAt(p, Vec2{(int)r,(int)c});
                ++enemyCount;
            }
        }
    }

    auto rooms = getRooms(*level);

    size_t playerRoom = rooms.size(), idx;
    if (level->getSpawnLocation() == Vec2{-1,-1}) {
        // Generate player spawn location but don't place player yet (the Game will 
        // spawn the player upon changing levels).
        playerRoom = getRand(0,rooms.size());
        idx = getRand(0,rooms[playerRoom].size());
        rooms[playerRoom].erase(rooms[playerRoom].begin() + idx);
        if (rooms[playerRoom].empty()) rooms.erase(rooms.begin() + playerRoom);

        level->setSpawnLocation(rooms[playerRoom][idx]);
    }

    if (level->getStairsLocation() == Vec2{-1,-1}) {
        // Generate stair spawn location
        size_t stairsRoom = getRand(0,rooms.size());
        if (stairsRoom == playerRoom && rooms.size() > 1)
            while (stairsRoom == playerRoom) 
                stairsRoom = getRand(0,rooms.size());

        idx = getRand(0,rooms[stairsRoom].size());
        level->setStairsLocation(rooms[stairsRoom][idx]);
        rooms[stairsRoom].erase(rooms[stairsRoom].begin() + idx);
        if (rooms[stairsRoom].empty()) rooms.erase(rooms.begin() + stairsRoom);

        level->getGrid().at(level->getStairsLocation())->setType(Tile::TileType::STAIR);
    }

    // Generate potions
    for (; potionCount < MAX_POTIONS; ++potionCount) {
        Potion::PotionType type = randomPotionType();
        level->spawnAt(Potion::makePotion(type), getNextSpawnLocation(rooms));
    }

    // Generate gold
    for (; goldCount < MAX_GOLD; ++goldCount) {
        level->spawnAt(randomGoldType(), getNextSpawnLocation(rooms));
    }

    // Generate entities
    for (; enemyCount < MAX_ENEMIES; ++enemyCount) {
        Race race = randomEnemyType();
        level->spawnAt(makeEntityWithRace(race), getNextSpawnLocation(rooms));
    }

    for (unsigned int r = 0; r < FLOOR_HEIGHT; ++r) {
        for (unsigned int c = 0; c < FLOOR_WIDTH; ++c) {
            if (auto hoardptr = dynamic_pointer_cast<DragonHoard>(theGrid[r][c]->getEntity()); hoardptr) {
                auto dragonDirection = static_cast<Direction>(getRand(0,static_cast<int>(Direction::CENTER)));
                auto dragonptr = makeEntityWithRace(Race::DRAGON);

                for (Direction dir = clockwise(dragonDirection); dir != dragonDirection; dir = clockwise(dir)) {
                    Vec2 loc = Vec2::stepVec(Vec2{(int)r,(int)c}, dir);
                    if (!theGrid[loc.x][loc.y]->isFloor() ||
                        theGrid[loc.x][loc.y]->getEntity()) continue;
                    level->spawnAt(dragonptr, loc);
                    hoardptr->setDragon(dynamic_pointer_cast<Dragon>(dragonptr));
                    dynamic_pointer_cast<Dragon>(dragonptr)->setGoldPile(hoardptr);
                    break;
                }
            }
        }
    }
    return level;
}

vector<vector<Vec2>> LevelFactory::getRooms(const Level &level) { // LeetCode 200
    vector<vector<bool>> visited(FLOOR_HEIGHT, vector(FLOOR_WIDTH, false));
    vector<vector<Vec2>> rooms{};

    auto grid = level.getGrid().viewTheGrid();

    for (size_t r = 0; r < FLOOR_HEIGHT; ++r) {
        for (size_t c = 0; c < FLOOR_WIDTH; ++c) {
            if (visited[r][c]
            || !grid[r][c]->isFloor()
            || grid[r][c]->getEntity()) continue;

            rooms.push_back(vector<Vec2>{});
            rooms.back().emplace_back(r,c);
            visited[r][c] = true;
            for (unsigned int i = 0; i < rooms.back().size(); ++i) {
                Vec2 pos = rooms.back()[i];
                if (pos.x > 0 && !visited[pos.x-1][pos.y]
                    && grid[pos.x-1][pos.y]->isFloor()) {
                    if (!grid[pos.x-1][pos.y]->getEntity())
                        rooms.back().push_back(Vec2{pos.x-1,pos.y});
                    visited[pos.x-1][pos.y] = true;
                }
                if (pos.x < (int)FLOOR_HEIGHT-1 && !visited[pos.x+1][pos.y]
                    && grid[pos.x+1][pos.y]->isFloor()) {
                    if (!grid[pos.x+1][pos.y]->getEntity())
                        rooms.back().push_back(Vec2{pos.x+1,pos.y});
                    visited[pos.x+1][pos.y] = true;
                }
                if (pos.y > 0 && !visited[pos.x][pos.y-1]
                    && grid[pos.x][pos.y-1]->isFloor()) {
                    if (!grid[pos.x][pos.y-1]->getEntity())
                        rooms.back().push_back(Vec2{pos.x,pos.y-1});
                    visited[pos.x][pos.y-1] = true;
                }
                if (pos.y < (int)FLOOR_WIDTH-1 && !visited[pos.x][pos.y+1]
                    && grid[pos.x][pos.y+1]->isFloor()) {
                    if (!grid[pos.x][pos.y+1]->getEntity())
                        rooms.back().push_back(Vec2{pos.x,pos.y+1});
                    visited[pos.x][pos.y+1] = true;
                }
            }
        }
    }

    return rooms;
}

// Randomly selects the next spawning location
static Vec2 getNextSpawnLocation(vector<vector<Vec2>> &rooms) {
    int room = getRand(0, rooms.size());
    int idx = getRand(0, rooms[room].size());
    Vec2 location = rooms[room][idx];
    rooms[room].erase(rooms[room].begin() + idx);
    if (rooms[room].empty()) rooms.erase(rooms.begin() + room);

    return location;
}

static Potion::PotionType randomPotionType() {
    int x = getRand(0, Potion::NUMPOTIONTYPES);
    switch (x) {
        case 0:
            return Potion::PotionType::HEALTH;
        case 1:
            return Potion::PotionType::ATTACK;
        case 2:
            return Potion::PotionType::DEFENSE;
        case 3:
            return Potion::PotionType::POISON;
        case 4:
            return Potion::PotionType::WEAK;
        case 5:
            return Potion::PotionType::BRITTLE;
        default:
            throw logic_error("You added a potion type without updating this function");
    }
}

static shared_ptr<Gold> randomGoldType() {
    int x = getRand(0,8);
    if (x <= 4) return make_shared<Gold>(2);
    if (x <= 5) return make_shared<DragonHoard>();
    else return make_shared<Gold>(1);
}

static Race randomEnemyType() {
    int x = getRand(0,18);
    if (x <= 3) return Race::HUMAN;
    if (x <= 6) return Race::DWARF;
    if (x <= 11) return Race::HALFLING;
    if (x <= 13) return Race::ELF;
    if (x <= 15) return Race::ORC;
    else return Race::MERCHANT;
}

static shared_ptr<Entity> charToLootPtr(char c) {
    switch (c) {
        case '0':
            return make_shared<HealthPotion>();
        case '1':
            return make_shared<AttackPotion>();
        case '2':
            return make_shared<DefensePotion>();
        case '3':
            return make_shared<PoisonPotion>();
        case '4':
            return make_shared<WeakPotion>();
        case '5':
            return make_shared<BrittlePotion>();
        case '6':
            return make_shared<Gold>(2);
        case '7':
            return make_shared<Gold>(1);
        case '8':
            return make_shared<Gold>(4);
        case '9':
            return make_shared<DragonHoard>();
        default:
            throw logic_error("Unreachable statement");
    }
}

static shared_ptr<Entity> charToEnemyPtr(char c) {
    switch (c) {
        case 'H':
            return makeEntityWithRace(Race::HUMAN);
        case 'W':
            return makeEntityWithRace(Race::DWARF);
        case 'E':
            return makeEntityWithRace(Race::ELF);
        case 'O':
            return makeEntityWithRace(Race::ORC);
        case 'M':
            return makeEntityWithRace(Race::MERCHANT);
        case 'D':
            return makeEntityWithRace(Race::DRAGON);
        case 'L':
            return makeEntityWithRace(Race::HALFLING);
        default:
            return nullptr;
    }
}
