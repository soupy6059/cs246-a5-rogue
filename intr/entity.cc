export module entity;

import <array>;
import util;
#include <memory>

export class Entity {
    class EntityImpl;
    class Status;
    std::unique_ptr<EntityImpl> data; // Enabling future strong exception guarentee
    virtual void step() = 0;
    virtual void mainUpdate();
    public:
    enum class Action { // im using Lucas' idea
        MOVE,
    };
    struct Status {
        Action action;
        Direction dir;
    };
    struct EntityImpl {
        static const NUMBER_OF_STATS = 3;
        enum class Stats {
            HEALTH, ATTACK, DAMAGE, // COUNT IS ABOVE. PLEASE UPDATE THE COUNT IF YOU CHANGE ENUM SIZE
        };
        std::array<int,NUMBER_OF_STATS> stats{0};
        Status status;
    };
    void setStatus(const Status &);
    const Status &getStatus();
    Entity(const EntityImpl &data);
    EntityImpl &getStats() const;
    virtual ~Entity() = default;
    void update(); 
};
