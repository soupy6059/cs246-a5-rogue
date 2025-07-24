#ifndef __enemy__
#define __enemy__

#include "character.h"
#include "util.h"

class Enemy : public Character {
  protected:
    void moveNewDir();
  public:
    virtual void attack(Tile& target) override;
    Enemy(CharacterDefaults d);
    virtual std::string icon() const override;
    virtual void step() override;
};

#endif
