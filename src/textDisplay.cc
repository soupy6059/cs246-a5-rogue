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

void TextDisplay::notify(Grid &grid) {
    ranges::transform(grid.viewTheGrid(), theDisplay, theDisplay.begin(), 
        [](const auto &tiles, const auto &display) {
            vector<char> newDisplay(display.size());
            ranges::transform(tiles, display, newDisplay.begin(),
                [](const auto &tile, const auto &_[[maybe_unused]]) {
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
