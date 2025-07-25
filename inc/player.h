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
    void printLevel(); // helper for notifying TextObserver
    virtual void mainUpdate() override; // needs to additional call notify TextObserver
    virtual void step() override; // gets input from std::cin
    struct defaultStats {
        int atk, def, hp, acc;
    };
    defaultStats defaults;
    public:
    Verb &refVerb();
    void appendVerb(Verb::Status); // appends an "action" for pretty printing
    Player(CharacterDefaults d);
    virtual ~Player() = default;
    virtual std::string icon() const override;
    virtual std::string getRaceName() const = 0; // get race name for pretty printing

    virtual void setHP(int n) override;
    void setATK(int n) override;
    void setDEF(int n) override;
    virtual int getScore() const;
    virtual void attack(Tile& t) override; // this attacks entity in t
    virtual std::string getName() const override; // get name for pretty printing
};

#endif
