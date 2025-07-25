#include "verb.h"

#include <iostream>

#include "character.h"

using namespace std;

Verb &Verb::append(string word) {
    action.push_back(word);
    return *this;
}

void Verb::appendStatus(Verb::Status status) {
    if(!action.empty()) append("and"s);
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
    case Verb::Action::ATTACK: {
        auto attacker = get<3>(status.data).first;
        auto target = get<3>(status.data).second;
        append(attacker->getName())
            .append("deals"s)
            .append(to_string(dynamic_pointer_cast<Character>(attacker)->getDamageDealt()))
            .append("damage"s)
            .append("to"s)
            .append(target->getName())
            .append("("s + to_string(dynamic_pointer_cast<Character>(target)->getHP()) + " HP)."s)
            .append(target->getName())
            .append("deals"s)
            .append(to_string(dynamic_pointer_cast<Character>(target)->getDamageDealt()))
            .append("to"s)
            .append(attacker->getName()); 
        } break;
    case Verb::Action::SEES_POTION:
        append(get<3>(status.data).first->getName())
            .append("sees"s)
            .append("a"s)
            .append(get<3>(status.data).second->getName());
        break;
    case Verb::Action::HOARD_THERE:
        append("The dragon is still alive"s);
        break;
    default:
        break;
    }
}
