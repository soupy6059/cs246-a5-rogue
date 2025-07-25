#ifndef __entity__
#define __entity__

#include <array>
#include <memory>
#include <variant>
#include <string>

#include "util.h"
#include "subjectObserver.h"

class Entity: public Subject {
public:  // "redeclared with different access"
    struct EntityImpl;
    struct Status;
private:
    std::unique_ptr<EntityImpl> data; // Enabling future strong exception guarentee
    virtual void step() = 0; // pure virtual method for an entities movement
    virtual void mainUpdate(); // virtual method for update's NonVirtualInterface
public:
    // what can a player notify about what it's doing / want's to do
    enum class Action {
        MOVE, NOTHING, INTERACT, ATTACK, KILL_ME, PRINT_LEVEL, QUIT, RESTART, PLAYER_DEATH,
    };

    // stores a status that is read on notify(Subject&)
    struct Status {
        Action action;
        std::variant<std::monostate,Direction> data;
    };

    // entityImpl's data for future Strong ESLG
    struct EntityImpl {
        Status status; // status for notifyObservers
        bool doubleRisk; // doubleRisk of updating twice (double; at risk of)
        static EntityImpl makeDefault(); // static method for easy entity making
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
    virtual std::string icon() const = 0;
    bool getDoubleRisk();
    void setDoubleRisk(bool);
    virtual std::string getName() const; // get name for pretty printing
};

#endif
