#ifndef __gold__
#define __gold__

#include "item.h"

class Gold: public Item {
    int value;
    public:
    Gold(int value);
    int getValue();
    virtual ~Gold() = default;
    virtual char icon() const override;
    virtual void step() override;
    virtual void affect(Entity&) override;
};

class DragonHoard: public Gold {
    public:
    DragonHoard(int);
    virtual ~DragonHoard() = default;
    bool hasDragon() const;
};

#endif
