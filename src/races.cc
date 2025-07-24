#include "races.h"
#include <memory>
#include <cmath>
#include <stdexcept>


using namespace std;

// HOW TO DO CUSTOM POTION EFFECT PLS HELP!!!
// SHADE
Shade::Shade(CharacterDefaults d): Player{d} {}

// Drow
Drow::Drow(CharacterDefaults d): Player{d} {}

// VAMPIRE
Vampire::Vampire(CharacterDefaults d): Player{d} {}

void Vampire::attack(Tile& target) {
    const int DWARF_DAMAGE = 5;
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Dwarf> d = std::dynamic_pointer_cast<Dwarf>(c);
    if (!c) return; // not a character
    float damage = ceil((100/(100 + static_cast<float>(c->getDEF()))) * static_cast<float>(atk));
    c->setHP(c->getHP() - static_cast<int>(damage)); // do damage
    if (d != nullptr) {
        c->setHP(c->getHP() - DWARF_DAMAGE); // reverse ability OOF
    } else {
        c->setHP(c->getHP() + DWARF_DAMAGE);
    }
    if (c->getHP() <= 0) {target.setEntity(nullptr);} // kill if dead
}

//Troll

Troll::Troll(CharacterDefaults d): Player{d} {}

void Troll::step() {
    Player::step();
    setHP(getHP() + 5);
}
// NEED TO DO SOMETHING ABOUT THE FUCKING +5 HP EVERY TURN
// GOBLIN

Goblin::Goblin(CharacterDefaults d): Player{d} {}

void Goblin::attack(Tile& target) {
    const int GOBLIN_FILTHY_CAPITALIST_BONUS = 5;
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Halfling> h = std::dynamic_pointer_cast<Halfling>(c);
    if (!c) return; // not a character
    float damage = ceil((100/(100 + static_cast<float>(c->getDEF()))) * static_cast<float>(atk));
    c->setHP(c->getHP() - static_cast<int>(damage)); // do damage
    if (c->getHP() <= 0) {
        target.setEntity(nullptr);
        setGold(getGold() + GOBLIN_FILTHY_CAPITALIST_BONUS);
    }
}


// HUMAN 
Human::Human(CharacterDefaults d): Enemy{d} {}
string Human::icon() const { return "\033[31;1mH\033[0m";}

// DWARF is DEFUALT

Dwarf::Dwarf(CharacterDefaults d): Enemy{d} {}
string Dwarf::icon() const { return "\033[31;1mW\033[0m";}

// ELF
Elf::Elf(CharacterDefaults d): Enemy{d} {}
string Elf::icon() const { return "\033[31;1mE\033[0m";}

void Elf::attack(Tile& target) {
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Drow> d = std::dynamic_pointer_cast<Drow>(c);
    int atk_count = (!d) ? 2 : 1;
    for (int i = 0; i < atk_count; ++i) {
        if (!c) return; // not a character
        float damage = ceil((100/(100 + static_cast<float>(c->getDEF()))) * static_cast<float>(atk));
        c->setHP(c->getHP() - static_cast<int>(damage)); // do damage
        if (c->getHP() <= 0) {target.setEntity(nullptr);}
    }
}

// ORC
Orc::Orc(CharacterDefaults d): Enemy{d} {}
string Orc::icon() const {return "\033[31;1mO\033[0m";}

void Orc::attack(Tile& target) {
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Goblin> g = std::dynamic_pointer_cast<Goblin>(c);
    if (!c) return; // not a character
    float damage = ceil((100/(100 + static_cast<float>(c->getDEF()))) * static_cast<float>(atk));
    if (!g) {
        damage += damage / 2;
    }
    c->setHP(c->getHP() - static_cast<int>(damage)); // do damage
    if (c->getHP() <= 0) {target.setEntity(nullptr);} // unprecdented murder
}

// MERCHANT
bool Merchant::isPissed = false;

Merchant::Merchant(CharacterDefaults d): Enemy{d} {}
string Merchant::icon() const {return "\033[31;1mM\033[0m";}

void Merchant::attack(Tile& target) {
    if (!isPissed) return;
    Enemy::attack(target);
}

void Merchant::togglePissed() {
    if (isPissed) return;
    isPissed = !isPissed;
}

void Merchant::step() {
    const int MERCHANT_BASE_HP = 30;
    if (hp < MERCHANT_BASE_HP) togglePissed();
    if (isPissed) { 
        bool canAttack = false;
        std::shared_ptr<Tile> playerLocation = playerTile(canAttack);
        if (playerLocation != nullptr) {attack(*playerLocation);}
    } else {
        Enemy::moveNewDir();
    }
}
// Dragon
Dragon::Dragon(CharacterDefaults d): Enemy{d} {}
string Dragon::icon() const { return "\033[31;1mD\033[0m";}

// HAFLING
Halfling::Halfling(CharacterDefaults d): Enemy{d} {}
string Halfling::icon() const {return "\033[31;1mL\033[0m";}

shared_ptr<Entity> makeEntityWithRace(Race race) {
    CharacterDefaults stats = getCharDefs(race);
    switch (race) {
        case Race::SHADE:
        return make_shared<Shade>(stats);
        case Race::DROW:
        return make_shared<Drow>(stats);
        case Race::VAMPIRE:
        return make_shared<Vampire>(stats);
        case Race::TROLL:
        return make_shared<Troll>(stats);
        case Race::GOBLIN:
        return make_shared<Goblin>(stats);
        case Race::HUMAN:
        return make_shared<Human>(stats);
        case Race::DWARF:
        return make_shared<Dwarf>(stats);
        case Race::ELF:
        return make_shared<Elf>(stats);
        case Race::ORC:
        return make_shared<Orc>(stats);
        case Race::DRAGON:
        return make_shared<Dragon>(stats);
        case Race::MERCHANT:
        return make_shared<Merchant>(stats);
        case Race::HALFLING:
        return make_shared<Halfling>(stats);
        default:
        throw logic_error("Not implemented!");
    }
}

CharacterDefaults getCharDefs(Race race) {
    switch (race) {
        case Race::SHADE:
        return {125, 25, 25, 100, 0};
        case Race::DROW:
        return {150, 25, 15, 100, 0};
        case Race::VAMPIRE:
        return {50, 25, 25, 100, 0};
        case Race::TROLL:
        return {120, 25, 15, 100, 0};
        case Race::GOBLIN:
        return {110, 15, 20, 100, 0};
        case Race::HUMAN:
        return {140, 20, 20, 50, 4};
        case Race::DWARF:
        return {100, 20, 30, 50, 0};
        case Race::ELF:
        return {140, 30, 10, 50, 0};
        case Race::ORC:
        return {180, 30, 25, 50, 0};
        case Race::DRAGON:
        return {150, 20, 20, 50, 0};
        case Race::MERCHANT:
        return {30, 70, 5, 50, 4};
        case Race::HALFLING:
        return {100, 15, 20, 50, 0};
        default:
        throw logic_error("Not implemented!");
    }
}
