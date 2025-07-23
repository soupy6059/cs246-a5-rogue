#include <iostream>
#include <vector>
#include <string>

#include "game.h"
#include "log.h"

using namespace std;

// TODO:
//
// 3) For some reason, Grid::notify(Tile&) is always called twice, when it shouldn't be.
//    3.1) NOTE: this isn't a bug per se, just weird. "seemingly" everything is fine

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
