export module grid;

import <vector>;
import <iostream>;

import tile;

export class Grid {
    class GridImpl;
    std::unique_ptr<GridImpl> data;
    void attachRelativeTileNeighbours(std::size_t,std::size_t);
    void attachTileNeighbours();
    public:
    Grid(std::size_t rowCount, std::size_t colCount);

    // testing
    void print(std::ostream&) const;
};


