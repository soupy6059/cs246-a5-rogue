#ifndef __tile__
#define __tile__

#include <variant>
#include <utility>

#include "subjectObserver.h"
#include "entity.h"
#include "util.h"
#include "gold.h"

class Tile: public Observer, public Subject {
public: // INTERNAL TYPES

    enum class Action {
        MOVE_OWNED_ENTITY, NOTHING, SWAP, INTERACT, ATTACK, ADJACENT_POTION,
    };

    // setStatus for notify, data is for sending data to notify(Subject)
    struct Status {
        Action action;
        std::variant<std::monostate,Direction,std::pair<Vec2,Vec2>> data;
    };

    enum class TileType {
        FLOOR,
        STAIR,
        HORIZONTAL_WALL,
        VERTICAL_WALL,
        HALLWAY,
        VOID,
        DOOR,
    };

    struct TileImpl {
        std::shared_ptr<Entity> entity; // managed entity, observes it by invariance
        std::shared_ptr<Entity> goldStorage; // because gold stays when an entity walks over it
        Status status; // for notify
        Vec2 position; // position of this tile in grid, avoids undefined Vec2
        TileType type;
    };

private: // DATA
    std::shared_ptr<TileImpl> data;
    
private: // PRIVATE HELPER METHODS
    // broadcasts the inentions of managed entity,
    // to change neighbours state, grid state, or own state
    void notify(Entity &);

    // managed recieving notifications from neighbours
    void notify(Tile &);

public: // CTOR & DTOR
    Tile(const TileImpl &);
    virtual ~Tile() = default;

public: // GETTERS AND SETTERS
    std::shared_ptr<Entity> getEntity() const;
    void setEntity(std::shared_ptr<Entity> toEntity);
    std::shared_ptr<Entity> moveEntity();

    const Status &getStatus() const;
    void setStatus(const Status &);

    const Vec2 &getPosition() const;
    void setPosition(const Vec2 &);

    const TileType &getType() const;
    void setType(const TileType &);

public: // VIRTUAL BEHAVIORS

    // decides which notify to call based on the type of whoFrom
    virtual void notify(Subject &whoFrom) override;

public: // METHODS

    static void swapTileEntities(Tile &a, Tile &b);

    // ask tile if something is possible
    void queryMovement(Entity &whoFrom);
    void queryInteraction(Entity &whoFrom);

    // do something if possible
    void queryInteraction(Tile &whoFrom); // handles if gold or potion affect is called
    void queryAttack(Tile &whoFrom); // them->entity->attack(this->entity)
    void queryMovement(Tile &whoFrom); // tileSwap(this->entity, them->entity)
    void queryPotion(Tile &whoFrom); // potion->affect(this->entity)

    Direction getRelativeDirection(const Tile &) const;
    bool pointingAt(const Tile &) const;
    bool isCollidable() const;
    bool isFloor() const;
    std::string icon() const;
};

Tile::TileType fromChar(char c);
#endif
