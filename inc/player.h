#ifndef __player__
#define __player__

#include <memory>

#include "subjectObserver.h"
#include "entity.h"
#include "character.h"
#include "verb.h"

class Player: public Character {
    Verb verb;
    protected:
    void printLevel();
    virtual void mainUpdate() override;
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
    virtual std::string icon() const override;
    virtual std::string getRaceName() const = 0;

    virtual void setHP(int n) override;
    void setATK(int n) override;
    void setDEF(int n) override;
    virtual void attack(Tile& t) override;
    virtual std::string getName() const override;
};

#endif
