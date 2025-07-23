#ifndef __player__
#define __player__

#include "subjectObserver.h"
#include "entity.h"
#include "character.h"

class Player: public Character {
    int gold = 0;
    virtual void step() override;
    protected:
    struct defaultStats {
        int atk, def, hp, acc;
    };
    defaultStats defaults;
    public:
    Player(int atk, int def, int hp, int acc);
    virtual ~Player() = default;
    virtual char icon() const override;
    void setGold(int);
    int getGold() const;
};

#endif
