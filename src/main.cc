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
        shared_ptr<Game> game = make_shared<Game>(args.at(1));
        game->attach(td);
        game->getPlayer()->attach(game);
        game->start();
        game->cleanUp();
    }
    catch(...) {
        shared_ptr<Game> game = make_shared<Game>();
        game->getPlayer()->attach(game);
        game->attach(td);
        game->start();
        game->cleanUp();
    }
}
