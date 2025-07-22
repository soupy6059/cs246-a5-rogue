#include "textDisplay.h"

#include <numeric>
#include <algorithm>
#include "util.h"
#include <utility>
using namespace std;

ostream &operator<<(ostream &os, const TextDisplay &td) {
    for(auto &$0: td.theDisplay) {
        for(const auto &ch: $0) os << ch;
        os << '\n'; // no flush
    }
    return os;
}

TextDisplay::TextDisplay(const Grid &grid):
    theDisplay(grid.viewTheGrid().size(), vector<char>(grid.viewTheGrid().at(0).size(), '.')) {}

// maps theDisplay to grid's icons.
// i think this function works.
void TextDisplay::notify(Grid &grid) {
    ranges::transform(grid.viewTheGrid(), theDisplay.begin(),
    [](const auto &tiles) {
        vector<char> newDisplay;
        ranges::transform(tiles, back_inserter(newDisplay),
        [](const auto &tile) {
            return tile->icon();
        });
        return newDisplay;
    });
}

void TextDisplay::notify(Subject &whoFrom) {
    try{
        notify(dynamic_cast<Grid&>(whoFrom));
        return;
    }
    catch(...) {}
    throw logic_error{"bad TextDisplay::notify() call"};
}
