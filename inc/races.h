#ifndef __race__
#define __race__

#include "tile.h"
#include "player.h"
#include "character.h"
#include "enemy.h"
#include "entity.h"
#include <memory>

// player classes inherit from player
class Shade : public Player {
    Shade(CharacterDefaults d);
};

class Drow : public Player {
    Drow(CharacterDefaults d);
    // custom potions
};

class Vampire : public Player {
  public:
    Vampire(CharacterDefaults d);
    void attack(Tile& t) override;
};

class Troll : public Player {
    Troll(CharacterDefaults d);
    // gets +5 hp everyturn
};

class Goblin : public Player {
    Goblin(CharacterDefaults d);
    void attack(Tile& t) override;
};

// enemy classes inherit from enemy
class Human : public Enemy {
    Human(CharacterDefaults d);
    // fully defualt from enemy
};

class Dwarf : public Enemy {
    Dwarf(CharacterDefaults d);
    // defualt (vampire take 5 dmg on attack)
};

class Elf : public Enemy {
    // double attack
    Elf(CharacterDefaults d);
    void attack(Tile& t) override; 
};

class Orc : public Enemy {
    // + 50% damage to goblins
    Orc(CharacterDefaults d);
    void attack(Tile& t) override;
};

class Merchant : public Enemy {
    static bool isPissed;
    public:
    Merchant(CharacterDefaults d);
    void togglePissed();
    void attack(Tile& t);
};

bool Merchant::isPissed = false;

class Dragon : public Enemy {
    Dragon(CharacterDefaults d);
    // custom move
};

class Halfling : public Enemy {
    Halfling(CharacterDefaults d);
    // player loses 50% accuracy
};

CharacterDefaults getCharDefs(Race race);

#endif
