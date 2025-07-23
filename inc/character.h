#ifndef __character__
#define __character__

#include "entity.h"
#include "util.h"
#include "tile.h"

class Character : public Entity {
  protected:
    int atk, def, hp, acc;
  public:
    virtual void attack(Tile& target);

    // getters
    int getATK();
    int getDEF();
    int getHP();
    int getACC();

    // setters
    virtual void setATK(int new_atk);
    virtual void setDEF(int new_def);
    virtual void setHP(int new_hp); // to maintain maximums
    void setACC(int new_acc);
    
    Character(CharacterDefaults d);
    virtual ~Character() = default;
    char icon() const override = 0;
};

#endif
