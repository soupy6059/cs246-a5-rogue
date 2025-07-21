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

TextDisplay::TextDisplay(const Grid &grid) {
    vector<size_t> iote(grid.viewTheGrid().size());
    for(const size_t _[[maybe_unused]]: iote) {
        theDisplay.emplace_back(grid.viewTheGrid().at(0).size(), '.');
    }
}

void TextDisplay::notify(Grid &grid) {
    ranges::transform(grid.viewTheGrid(), theDisplay, theDisplay.begin(), 
        [](const vector<shared_ptr<Tile>> &tiles, const vector<char> &display) -> vector<char> {
            vector<char> newDisplay(display.size());
            ranges::transform(tiles, display, newDisplay.begin(),
                [](const shared_ptr<Tile> &tile, const char &_[[maybe_unused]]) -> char {
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
