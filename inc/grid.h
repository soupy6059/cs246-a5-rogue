#ifndef __grid__
#define __grid__

#include <vector>
#include <iostream>

#include "tile.h"

class Grid {
    struct GridImpl {
        std::vector<std::vector<std::shared_ptr<Tile>>> theGrid; // *theGrid[row][col]
    };
    std::unique_ptr<GridImpl> data;
    void attachRelativeTileNeighbours(const int, const int);
    void attachTileNeighbours();
    public:
    Grid(std::size_t rowCount, std::size_t colCount);
    virtual ~Grid() = default;

    // testing
    void print(std::ostream&) const;
};

#endif
