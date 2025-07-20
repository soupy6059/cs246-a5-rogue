#ifndef __grid__
#define __grid__

#include <vector>
#include <iostream>

#include "tile.h"
#include "util.h"

class Grid: public Observer {
    struct GridImpl {
        std::vector<std::vector<std::shared_ptr<Tile>>> theGrid; // *theGrid[row][col]
    };
    std::unique_ptr<GridImpl> data;
    void attachRelativeTileNeighbours(const int, const int);
    void attachTileNeighbours();
    public:
    std::vector<std::vector<std::shared_ptr<Tile>>> &getTheGrid();
    Grid(std::size_t rowCount, std::size_t colCount);
    std::shared_ptr<Tile> at(std::size_t row, std::size_t col) const;
    std::shared_ptr<Tile> at(const Vec2 &) const;
    virtual ~Grid() = default;
    virtual void notify(Subject&) override;
    void notify(Tile&);

    // testing
    void print(std::ostream&) const;
};

#endif
