#ifndef __enemy__
#define __enemy__

#include "character.h"
#include "util.h"

class Enemy : public Character {
  static bool canMove;
  protected:
    void moveNewDir();
    std::shared_ptr<Tile> playerTile(bool &found);
  public:
    virtual void attack(Tile& target) override;
    Enemy(CharacterDefaults d);
    virtual std::string icon() const override;
    virtual void step() override;
    void toggleCanMove();
    bool canItMove();
};

#endif
