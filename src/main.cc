#include <iostream>
#include <vector>
#include <string>

#include "races.h"
#include "game.h"
#include "log.h"
#include "textDisplay.h"

using namespace std;

void getUserInput(Race &startingRace) {
    while (true) {
        std::string input;
        std::cout << "Select your race with s, d, v, g, t\n or enter q to quit" << std::endl;
        std::cin >> input;
        if (!cin) {
            break;
        }
        if (input == "q") break;
        if (input == "s") {
            startingRace = Race::SHADE;
            break;
        } else if (input == "d") {
            //drow
            startingRace = Race::DROW;
            break;
        } else if (input == "v") {
            // vampire
            startingRace = Race::VAMPIRE;
            break;
        } else if (input == "g") {
            // goblin
            startingRace = Race::GOBLIN;
            break;
        } else if (input == "t") {
            // troll
            startingRace = Race::TROLL;
            break;
        }
    } //while
}

int main(int argc, char **argv) {
    vector<string> args;
    for(int i{0}; i < argc; ++i) args.push_back(string{argv[i]});

    Log::initLogs();
    shared_ptr<TextDisplay> td = make_shared<TextDisplay>();
    Race userChoice;
    getUserInput(userChoice);
    try{
        shared_ptr<Game> game = make_shared<Game>("assets/level-empty.txt", 0, userChoice);
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
