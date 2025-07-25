#include <iostream>
#include <vector>
#include <string>

#include "races.h"
#include "game.h"
#include "log.h"
#include "textDisplay.h"

using namespace std;

int getUserInput(Race &startingRace) {
    while (true) {
        string input;
        cout << "Select your race with s, d, v, g, t\nor enter q to quit" << endl;
        getline(cin, input);
        if (!cin) { return -1; }
        if (input == "q") return -1;
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
    cin.clear();
    return 0;
}

int main(int argc, char **argv) {
    vector<string> args;
    for(int i{0}; i < argc; ++i) args.push_back(string{argv[i]});

    bool playAgain = true;
    Log::initLogs();
    while (playAgain) {
        shared_ptr<TextDisplay> td = make_shared<TextDisplay>();
        Race userChoice = Race::SHADE;
        if(getUserInput(userChoice) == -1) return 0;
        
        int seed = 0;
        try {
            seed = stoi(args.at(2));
        }
        catch(...) {}
        
        shared_ptr<Game> game = nullptr;
        try {
            game = make_shared<Game>(args.at(1), seed, userChoice);
        }
        catch(...) {
            game = make_shared<Game>("assets/level-empty.txt", seed, userChoice);
        }
        game->attach(td);
        game->getPlayer()->attach(game);
        playAgain = game->start();
    }
}
