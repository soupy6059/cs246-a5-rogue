#ifndef __enemy__
#define __enemy__

#include "character.h"
#include "util.h"

class Enemy : public Character {
  public:
    virtual void attack(Tile& target) = 0;
    void step() override;
};

#endif