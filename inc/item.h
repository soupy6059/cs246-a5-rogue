#ifndef __item__
#define __item__

#include "entity.h"

// interactable
class Item: public Entity {
public:
    Item(const Entity::EntityImpl &data); 
    virtual ~Item() = default;
    virtual char icon() const override;
    virtual void affect(Entity&) = 0;
};

#endif
