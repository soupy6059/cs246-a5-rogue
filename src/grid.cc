#include "grid.h"

#include <utility>
#include <iostream>

using namespace std;

#include "tile.h"

Grid::Grid(size_t rowCount, size_t colCount):
    data{nullptr} {
    vector<vector<shared_ptr<Tile>>> toTheGrid;
    toTheGrid.reserve(rowCount);
    for(size_t r = 0; r < rowCount; ++r) {
        vector<shared_ptr<Tile>> column;
        column.reserve(colCount);
        for(size_t c = 0; c < colCount; ++c) {
            column.emplace_back(make_shared<Tile>(nullptr));
        }
        toTheGrid.push_back(column);
    }
    data = unique_ptr<GridImpl>{new GridImpl{
        .theGrid = move(toTheGrid),
    }};
    attachTileNeighbours();
}

void Grid::print(ostream &os) const {
    for(const vector<shared_ptr<Tile>> &row: this->data->theGrid) {
        for(const shared_ptr<Tile> &tile: row) {
            os << tile->icon() << endl;
        }
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
        for(signed c {0}; c < static_cast<signed>(data->theGrid.size()); ++c) {
            attachRelativeTileNeighbours(r, c);
        }
    }
}
