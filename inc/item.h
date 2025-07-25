#ifndef __item__
#define __item__

#include "entity.h"

// interactable
class Item: public Entity {
    bool autoPickup = false;
public:
    Item(bool autoPickup = false); 
    virtual ~Item() = default;
    virtual std::string icon() const override;
    virtual void step() override;
    virtual void affect(Entity&) = 0; // what happens when player notifes INTERACT
};

#endif
