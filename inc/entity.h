#ifndef __entity__
#define __entity__

#include <array>
#include <memory>
#include <variant>

#include "util.h"
#include "subjectObserver.h"

class Entity: public Subject {
public:  // "redeclared with different access"
    struct EntityImpl;
    struct Status;
private:
    std::unique_ptr<EntityImpl> data; // Enabling future strong exception guarentee
    virtual void step() = 0;
    virtual void mainUpdate();
public:
    enum class Action { // im using Luke's idea
        MOVE, NOTHING, INTERACT, ATTACK, KILL_ME,
    };
    struct Status {
        Action action;
        std::variant<std::monostate,Direction> data;
    };
    struct EntityImpl {
        Status status;
        bool doubleRisk;
        static EntityImpl makeDefault();
    };
    Entity(const EntityImpl &data = EntityImpl::makeDefault());
    Entity(const Entity &other);
    Entity(Entity &&other);
    Entity &operator=(const Entity &other);
    Entity &operator=(Entity &&other);
    virtual ~Entity() = default;
    void setStatus(const Status &);
    const Status &getStatus();
    EntityImpl &getStats() const;
    void update(); 
    virtual char icon() const = 0;
    bool getDoubleRisk();
    void setDoubleRisk(bool);
};


#endif
