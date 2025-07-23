#ifndef __enemy__
#define __enemy__

#include "character.h"
#include "util.h"

class Enemy : public Character {
  public:
    virtual void attack(Tile& target) override;
    Enemy(CharacterDefaults d);
    void step() override;
    virtual char icon() const override;
};

#endif
