#ifndef __player__
#define __player__

#include "subjectObserver.h"
#include "entity.h"
#include "character.h"
#include "verb.h"

class Player: public Character {
    Verb verb;
    protected:
    virtual void step() override;
    struct defaultStats {
        int atk, def, hp, acc;
    };
    defaultStats defaults;
    public:
    Verb &refVerb();
    void appendVerb(Verb::Status);
    Player(CharacterDefaults d);
    virtual ~Player() = default;
    virtual char icon() const override;

    virtual void setHP(int n) override;
    void setATK(int n) override;
    void setDEF(int n) override;
    virtual void attack(Tile& t) override;
};

#endif
