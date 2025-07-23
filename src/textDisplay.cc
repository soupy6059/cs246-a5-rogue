#include "textDisplay.h"

#include <iostream>
#include <iomanip>

#include "game.h"
#include "level.h"

using namespace std;

void TextDisplay::notify(Subject &whoFrom) {
    Game &game = dynamic_cast<Game&>(whoFrom);
    game.refCurrentLevel().getGrid().print(cout);
    string race = "DEFAULT";
    string _ = "Race: "s + race + " \033[33;1mGold\033[0m: "s + to_string(game.getPlayer()->getGold());
    cout << setw(FLOOR_WIDTH - 10) << left << _
         << "Floor "s << game.getCurrentLevelIndex()
         << endl;
    cout << "\033[32;1mHP\033[0m: "s << game.getPlayer()->getHP() << endl;
    cout << "\033[31;1mATK\033[0m: "s << game.getPlayer()->getATK() << endl;
    cout << "\033[94;1mDEF\033[0m: "s << game.getPlayer()->getDEF() << endl;
    cout << "\033[1mAction\033[0m: "s;
    for(size_t i{0}; i < game.getPlayer()->refVerb().action.size(); ++i) {
        cout << game.getPlayer()->refVerb().action.at(i);
        if(i < game.getPlayer()->refVerb().action.size() - 1) cout << " ";
    }
    cout << endl;
    game.getPlayer()->refVerb().action.clear();
}
