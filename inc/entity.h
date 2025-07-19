#ifndef __entity__
#define __entity__

#include <array>
#include "util.h"
#include <memory>

class Entity {
public:  // "redeclared with different access"
    struct EntityImpl;
    struct Status;
private:
    std::unique_ptr<EntityImpl> data; // Enabling future strong exception guarentee
    virtual void step() = 0;
    virtual void mainUpdate();
public:
    enum class Action { // im using Lucas' idea
        MOVE, NOTHING
    };
    struct Status {
        Action action;
        Direction dir;
    };
    struct EntityImpl {
        static const std::size_t NUMBER_OF_STATS = 3;
        enum class Stats {
            HEALTH, ATTACK, DAMAGE, // COUNT IS ABOVE. PLEASE UPDATE
        };
        std::array<int,NUMBER_OF_STATS> stats{0};
        Status status;
    };
    Entity(const EntityImpl &data);
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
};

#endif
