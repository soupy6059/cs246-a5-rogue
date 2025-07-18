export module tile;

import subjectObserver;

export class Tile: public Observer, public Subject {
    class Status;
    std::shared_ptr<Entity> entity;
    std::shared_ptr<Status> status;
    std::shared_ptr<Vec2> position;
    void notify(Entity &);
    public:
    enum class TileType {
        FLOOR,
        STAIR,
        WALL,
        HALLWAY,
        VOID,
        DOOR,
    };
    enum class Action {
        MOVE_OWNED_ENTITY,
    };
    struct Status {
        Action action;
        Direction dir;
    };
    private: TileType type;
    public:
    Tile(std::shared_ptr<Entity> entity);
    virtual void notify(Subject &whoFrom) override;
    std::shared_ptr<Entity> getEntity() const;
    void setEntity(std::shared_ptr<Entity> toEntity);
    std::shared_ptr<Entity> moveEntity() const;
    bool isCollidable() const;

    const Status &getStatus() const;
    void setStatus(const Status &);

    bool pointingAt(const Tile &) const;

    // testing (i believe this will be handled in textDisplay ask ian)
    char icon() const;
};
