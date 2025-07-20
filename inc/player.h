#ifndef __player__
#define __player__

#include "subjectObserver.h"
#include "entity.h"

class Player: public Entity {
    virtual void step() override;
    public:
    Player(const Entity::EntityImpl &data);
    virtual ~Player() = default;
    virtual char icon() const override;
};

#endif
