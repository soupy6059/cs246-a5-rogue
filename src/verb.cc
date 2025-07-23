#include "verb.h"

#include <iostream>

using namespace std;

Verb &Verb::append(string word) {
    action.push_back(word);
    return *this;
}

void Verb::appendStatus(Verb::Status status) {
    cout << "is this code runnnign?" << endl;
    if(!empty) append("and"s);
    switch(status.action) {
    case Verb::Action::SPAWN:
        append("Player"s)
            .append("character"s)
            .append("has"s)
            .append("spawned"s);
        break;
    case Verb::Action::MOVE:
        append(get<pair<shared_ptr<Entity>,Direction>>(status.data).first->getName())
            .append("moves"s)
            .append(dirToStr(get<pair<shared_ptr<Entity>,Direction>>(status.data).second));
        break;
    case Verb::Action::ATTACK:
        append(get<3>(status.data).first->getName())
            .append("attacked"s)
            .append(get<3>(status.data).second->getName());
        break;
    default:
        break;
    }
}
