export module grid;

import <vector>;

import tile;

export class Grid {
    class GridImpl;
    std::unique_ptr<GridImpl> data;
    public:
    Grid(std::size_t rowCount, std::size_t colCount);
};
