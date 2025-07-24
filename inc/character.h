#ifndef __character__
#define __character__

#include "entity.h"
#include "util.h"
#include "tile.h"

class Character : public Entity {
  protected:
    int atk, def, hp, acc, gold;
    int deltaAtk = 0, deltaDef = 0;
    int damageDealt = 0; // tracks the damage taken from being attacked
  public:
    // applies the damage done via combat to the target
    virtual void attack(Tile& target);

    // getters
    int getATK() const;
    int getDEF() const;
    int getHP() const;
    int getACC() const;
    int getGold() const;
    int getDamageDealt() const;
    // returns the damage that "would" be done upon attacking
    virtual int getDamage(Tile& target);

    // setters
    virtual void setATK(int new_atk);
    virtual void setDEF(int new_def);
    virtual void setHP(int new_hp); // to maintain maximums
    void setACC(int new_acc);
    void setGold(int new_gold);
    void setDamageDealt(int damage);

    void changeDeltaATK(int deltaDeltaAtk);
    void changeDeltaDEF(int deltaDeltaDEF);
    void resetDeltaStats();
    
    Character(CharacterDefaults d);
    virtual ~Character() = default;
    virtual std::string icon() const override = 0;

};

#endif
