#ifndef __race__
#define __race__

#include "tile.h"
#include "player.h"
#include "character.h"
#include "enemy.h"
#include <memory>

// player classes inherit from player
class Shade : public Player, public Character {
    // default everything
    void setHP(int n) override;

};

class Drow : public Player, public Character {
    // defualt attack
    void setHP(int n) override;
    // custom potions
};

class Vampire : public Player, public Character {
  public:
    void attack(Tile& t) override;
};

class Troll : public Player, public Character {
  public:
    void setHP(int n) override;
};

class Goblin : public Player, public Character {
    void setHP(int n) override;
    void attack(Tile& t) override;
};

// enemy classes inherit from enemy
class Human : public Enemy {
    // fully defualt from enemy
};

class Dwarf : public Enemy {
    // defualt (vampire take 5 dmg on attack)
};

class Elf : public Enemy {
    // double attack
    void attack(Tile& t) override; 
};

class Orc : public Enemy {
    // + 50% damage to goblins
    void attack(Tile& t) override;
};

class Merchant : public Enemy {
    static bool isPissed;
    public:
    void togglePissed();
    void attack(Tile& t);
};

bool Merchant::isPissed = false;

class Dragon : public Enemy {
    // custom move
};

class Halfling : public Enemy {
    // player loses 50% accuracy
};
#endif
