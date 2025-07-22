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
// 3) For some reason, Grid::notify(Tile&) is always called twice, when it shouldn't be.
//    3.1) NOTE: this isn't a bug per se, just weird. "seemingly" everything is fine
// 4) TextDisplay is completely bugged to shit

int main(int argc, char **argv) {
    vector<string> args;
    for(int i{0}; i < argc; ++i) args.push_back(string{argv[i]});

    Log::initLogs();
    
    try{
        Game game{args.at(1)};
        game.start();
    }
    catch(...) {
        Game game;
        game.start();
    }
}
