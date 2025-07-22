#ifndef __enemy__
#define __enemy__

#include "character.h"
#include "util.h"

class Enemy : public Character {
    int droppableLoot;
  public:
    virtual void attack(Tile& target) override = 0;
    void step() override;
};

#endif