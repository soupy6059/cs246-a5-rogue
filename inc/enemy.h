#ifndef __enemy__
#define __enemy__

#include "character.h"
#include "util.h"

class Enemy : public Character {
    int droppableLoot;
  public:
    virtual void attack(Tile& target) override;
    Enemy(EntityImpl data, int atk, int def, int hp, int acc, int loot);
    void step() override;
    void setLoot(int n);
    int getLoot();
};

#endif