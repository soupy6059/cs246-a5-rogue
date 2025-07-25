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
        std::shared_ptr<Entity> entity;
        std::shared_ptr<Entity> goldStorage;
        Status status;
        Vec2 position;
        TileType type;
    };

private: // DATA
    std::shared_ptr<TileImpl> data;
    
private: // PRIVATE HELPER METHODS
    void notify(Entity &);
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
    virtual void notify(Subject &whoFrom) override;

public: // METHODS
    static void swapTileEntities(Tile &a, Tile &b);
    void queryMovement(Tile &whoFrom);
    void queryPotion(Tile &whoFrom);
    void queryMovement(Entity &whoFrom);
    void queryInteraction(Entity &whoFrom);
    void queryInteraction(Tile &whoFrom);
    void queryAttack(Tile &whoFrom);
    Direction getRelativeDirection(const Tile &) const;
    bool pointingAt(const Tile &) const;
    bool isCollidable() const;
    bool isFloor() const;
    std::string icon() const;
};

Tile::TileType fromChar(char c);
#endif
