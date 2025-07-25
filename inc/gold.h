#ifndef __gold__
#define __gold__

#include "item.h"
#include <memory>

class Gold: public Item {
    int value;
    public:
    Gold(int value);
    int getValue();
    virtual ~Gold() = default;
    virtual std::string icon() const override;
    virtual void step() override; // cant move
    virtual void affect(Entity&) override; // addGold(); killMe();
};

class Dragon;
class DragonHoard: public Gold {
    std::shared_ptr<Dragon> myDragon = nullptr;
    public:
    DragonHoard();
    virtual ~DragonHoard() = default;
    void setDragon(std::shared_ptr<Dragon>);
    virtual void mainUpdate() override;
    bool hasDragon() const;
};

#endif
