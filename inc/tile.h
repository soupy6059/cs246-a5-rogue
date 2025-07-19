#ifndef __tile__
#define __tile__

#include "subjectObserver.h"
#include "entity.h"
#include "util.h"

class Tile: public Observer, public Subject {
public: // INTERNAL TYPES
    enum class Action {
        MOVE_OWNED_ENTITY,
    };
    struct Status {
        Action action;
        Direction dir;
    };
    enum class TileType {
        FLOOR,
        STAIR,
        WALL,
        HALLWAY,
        VOID,
        DOOR,
    };

private: // DATA
    std::shared_ptr<Entity> entity;
    std::shared_ptr<Status> status;
    std::shared_ptr<Vec2> position;
    TileType type;

private: // PRIVATE HELPER METHODS
    void notify(Entity &);
    void notify(Tile &);

public: // CTOR & DTOR
    Tile(std::shared_ptr<Entity> entity);
    virtual ~Tile() = default;

public: // GETTERS AND SETTERS
    std::shared_ptr<Entity> getEntity() const;
    void setEntity(std::shared_ptr<Entity> toEntity);
    std::shared_ptr<Entity> moveEntity() const;

    const Status &getStatus() const;
    void setStatus(const Status &);

public: // VIRTUAL BEHAVIORS
    virtual void notify(Subject &whoFrom) override;

public: // METHODS
    void queryMovement(Tile &whoFrom);
    void queryMovement(Entity &whoFrom);
    Direction getRelativeDirection(const Tile &) const;
    bool pointingAt(const Tile &) const;
    bool isCollidable() const;
    char icon() const; // testing (i believe this will be handled in textDisplay, ask ian)
};
#endif
