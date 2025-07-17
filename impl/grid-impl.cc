module grid;

import <utility>;

using namespace std;

struct Grid::GridImpl {
    vector<vector<Tile>> theGrid; // [row][col]
};

Grid::Grid(size_t rowCount, size_t colCount):
    data{make_unique<GridImpl>()} {
    vector<vector<Tile>> toTheGrid
    toTheGrid.reserve(rowCount);
    for(size_t r = 0; r < rowCount; ++r) {
        vector<Tile> column;
        column.reserve(colCount);
        for(size_t c = 0; c < colCount; ++c) {
            column.emplace_back(nullptr);
        }
        toTheGrid.push_back(column);
    }
    swap(this->data->theGrid, toTheGrid);
}
