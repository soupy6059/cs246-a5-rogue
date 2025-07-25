#ifndef __race__
#define __race__

#include "tile.h"
#include "player.h"
#include "enemy.h"

enum class Race {
    SHADE,
    DROW,
    VAMPIRE,
    TROLL,
    GOBLIN,
    HUMAN,
    DWARF,
    ELF,
    ORC,
    DRAGON,
    MERCHANT,
    HALFLING,
};

// player classes inherit from player
class Shade : public Player {
public:
    Shade(CharacterDefaults d);
    std::string getRaceName() const override;
    int getScore() const override;
};

class Drow : public Player {
public:
    Drow(CharacterDefaults d);
    std::string getRaceName() const override;
    // custom potions
};

class Vampire : public Player {
  public:
    Vampire(CharacterDefaults d);
    void attack(Tile& t) override;
    std::string getRaceName() const override;
    void setHP(int n) override;
};

class Troll : public Player {
public:
    Troll(CharacterDefaults d);
    void step() override;
    std::string getRaceName() const override;
    // gets +5 hp everyturn
};

class Goblin : public Player {
public:
    Goblin(CharacterDefaults d);
    void attack(Tile& t) override;
    std::string getRaceName() const override;
};

// enemy classes inherit from enemy
class Human : public Enemy {
public:
    Human(CharacterDefaults d);
    std::string icon() const override;
    // fully defualt from enemy
};

class Dwarf : public Enemy {
public:
    Dwarf(CharacterDefaults d);
    std::string icon() const override;
    // defualt (vampire take 5 dmg on attack)
};

class Elf : public Enemy {
public:
    // double attack
    Elf(CharacterDefaults d);
    void attack(Tile& t) override;
    std::string icon() const override; 
};

class Orc : public Enemy {
public:
    // + 50% damage to goblins
    Orc(CharacterDefaults d);
    void attack(Tile& t) override;
    std::string icon() const override;
};

class Merchant : public Enemy {
    static bool isPissed;
    public:
    Merchant(CharacterDefaults d);
    void attack(Tile& t) override;
    std::string icon() const override;
    void step() override;
    void togglePissed();
};

class Dragon : public Enemy {
    std::weak_ptr<Entity> myGold;
public:
    Dragon(CharacterDefaults d);
    void step() override;
    std::string icon() const override;
    void setGoldPile(std::shared_ptr<Entity> goldPilePointer);
    // custom move
};

class Halfling : public Enemy {
public:
    Halfling(CharacterDefaults d);
    std::string icon() const override;
    // player loses 50% accuracy
};

std::shared_ptr<Entity> makeEntityWithRace(Race race);

CharacterDefaults getCharDefs(Race race);

#endif
