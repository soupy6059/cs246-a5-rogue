#include "grid.h"

#include <utility>
#include <iostream>
#include <cassert>

#include "tile.h"
#include "log.h"

using namespace std;


std::shared_ptr<Tile> Grid::at(std::size_t row, std::size_t col) const {
    return data->theGrid.at(row).at(col);
}

std::shared_ptr<Tile> Grid::at(const Vec2 &location) const {
    return at(location.x, location.y);
}

Grid::Grid(size_t rowCount, size_t colCount):
    data{nullptr} {
    vector<vector<shared_ptr<Tile>>> toTheGrid;
    toTheGrid.reserve(rowCount);
    for(size_t r = 0; r < rowCount; ++r) {
        vector<shared_ptr<Tile>> column;
        column.reserve(colCount);
        for(size_t c = 0; c < colCount; ++c) {
            column.emplace_back(make_shared<Tile>(Tile::TileImpl{
                .entity = nullptr,
                .status = Tile::Status{
                    .action = Tile::Action::NOTHING,
                    .dir = Direction::CENTER,
                    .selfPosition = {0,0},
                    .otherPosition = {0,0},
                },
                .position = Vec2{static_cast<int>(r),static_cast<int>(c)},
                .type = Tile::TileType::FLOOR,
            }));
        }
        toTheGrid.push_back(column);
    }
    data = unique_ptr<GridImpl>{new GridImpl{
        .theGrid = move(toTheGrid),
    }};
    attachTileNeighbours();
}

vector<vector<shared_ptr<Tile>>> &Grid::getTheGrid() {
    return data->theGrid;
}

void Grid::notify(Tile &whoFrom) {
    if(whoFrom.getStatus().action == Tile::Action::SWAP) {
        shared_ptr<Tile> self = at(whoFrom.getStatus().selfPosition);
        shared_ptr<Tile> other = at(whoFrom.getStatus().otherPosition);
        if(!self->getEntity()) { return; } // this really should throw an error, but I'm not sure how to stop the bad call itself

        self->getEntity()->detach(self);
        shared_ptr<Entity> entity = self->getEntity();
        self->setEntity(nullptr);
        other->setEntity(entity);
        other->getEntity()->attach(other);

        assert(!self->getEntity());
        assert(other->getEntity());
        return;
    }
    throw logic_error{"grid should only be called w/ notify observers when a Tile wants to SWAP"};
}

void Grid::notify(Subject &whoFrom) {
    try{ notify(dynamic_cast<Tile&>(whoFrom)); }
    catch(...) {}
}

void Grid::print(ostream &os) const {
    for(const vector<shared_ptr<Tile>> &row: this->data->theGrid) {
        for(const shared_ptr<Tile> &tile: row) {
            os << tile->icon();
        }
        os << endl;
    }
}

void Grid::attachRelativeTileNeighbours(const int r, const int c) {
    auto tile {data->theGrid.at(r).at(c)};
    for(int i {-1}; i <= 1; ++i) {
        for(int j {-1}; j <= 1; ++j) {
            if(r + i < 0 || c + j < 0 || (i == 0 && j == 0)) {
                continue;
            }
            try{
                int di = r + i;
                int dj = c + j;
                auto nb {
                    data->theGrid
                        .at(static_cast<size_t>(di))
                        .at(static_cast<size_t>(dj))
                };
                tile->attach(nb);
            }
            catch(...) {} // slow b/c of try catch run, fix if you want but this works.
                          // and it's only run one per level, of which there are 5
        }
    }
}

void Grid::attachTileNeighbours() {
    for(signed r {0}; r < static_cast<signed>(data->theGrid.size()); ++r) {
        for(signed c {0}; c < static_cast<signed>(data->theGrid.at(0).size()); ++c) {
            attachRelativeTileNeighbours(r, c);
            Log::getLogFile("neighbourCount") << at(Vec2{r,c})->getObservers().size() << endl;
        }
    }
}
