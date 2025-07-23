#include <iostream>
#include <vector>
#include <string>

#include "game.h"
#include "log.h"
#include "textDisplay.h"

using namespace std;

int main(int argc, char **argv) {
    vector<string> args;
    for(int i{0}; i < argc; ++i) args.push_back(string{argv[i]});

    Log::initLogs();
    shared_ptr<TextDisplay> td = make_shared<TextDisplay>();
    
    try{
        Game game{args.at(1)};
        game.attach(td);
        game.start();
    }
    catch(...) {
        Game game;
        game.attach(td);
        game.start();
    }
}
