export module tile;

import subjectObserver;


export class Tile: public Observer, public Subject {
    std::shared_ptr<Entity> entity;
    public:
    enum class TileType {
        FLOOR,
        STAIR,
        WALL,
        HALLWAY,
        VOID,
        DOOR,
    };
    private: TileType type;
    public:
    Tile(std::shared_ptr<Entity> entity);
    virtual void notify(Subject &whoFrom) override;
    std::shared_ptr<Entity> getEntity() const;
    bool isCollidable() const;

};
