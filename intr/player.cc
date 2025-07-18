export module player;

export class Player: public Subject, public Entity {
    virtual void step() override;
    public:
    Player(const Entity::EntityImpl &data);
    ~Player() = default;
};
