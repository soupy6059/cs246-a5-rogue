#ifndef __player__
#define __player__

#include "subjectObserver.h"
#include "entity.h"
#include "character.h"

class Player: public Character {
    virtual void step() override;
    protected:
    int gold;
    struct defaultStats {
        int atk, def, hp, acc;
    };
    defaultStats defaults;
    public:
    Player(CharacterDefaults d);
    virtual ~Player() = default;
    virtual char icon() const override;
    void setGold(int);
    int getGold() const;

    virtual void setHP(int n) override;
    void setATK(int n) override;
    void setDEF(int n) override;
    virtual void attack(Tile& t) override;
};

#endif
