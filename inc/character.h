#ifndef __character__
#define __character__

#include "entity.h"
#include "util.h"
#include "tile.h"

class Character : public Entity {
  protected:
    int atk, def, hp, acc, gold;
    int deltaAtk = 0, deltaDef = 0;
  public:
    virtual void attack(Tile& target);

    // getters
    int getATK();
    int getDEF();
    int getHP();
    int getACC();
    int getGold();

    // setters
    virtual void setATK(int new_atk);
    virtual void setDEF(int new_def);
    virtual void setHP(int new_hp); // to maintain maximums
    void setACC(int new_acc);
    void setGold(int new_gold);

    void changeDeltaATK(int deltaDeltaAtk);
    void changeDeltaDEF(int deltaDeltaDEF);
    
    Character(CharacterDefaults d);
    virtual ~Character() = default;
    virtual std::string icon() const override = 0;

};

#endif
