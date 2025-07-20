#include <iostream>
#include <vector>
#include <string>

#include "game.h"
#include "log.h"

using namespace std;

// TODO:
//
// 1) handle entity spawning better.
//    1.1) noting that they have to attach() their tile b/c entity is a subject
//    1.2) and src/game.cc:start() has an "example" of how to do it in the ugly way
// 2) Fix src/player.cc:step. i forgot how to properly do input so i used labels which is bad

int main() { try {
    Log::initLogs();
    Game game;
    game.start();
}
catch(const exception &ex) {
    cerr << ex.what() << endl;
    return -1;
}}
