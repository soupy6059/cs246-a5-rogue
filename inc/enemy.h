#ifndef __enemy__
#define __enemy__

#include "character.h"

class Enemy : public Character {
  public:
    virtual void attack(Tile& target) = 0;
    void step() override;
    void
};

#endif