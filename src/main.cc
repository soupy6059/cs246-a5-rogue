#include <iostream>
#include <vector>

#include "game.h"

using namespace std;

int main() { try {
    Game game;
    game.start();
}
catch(const exception &ex) {
    cerr << ex.what() << endl;
    return -1;
}}
