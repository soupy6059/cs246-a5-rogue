#ifndef __potion__
#define __potion__

class Potion: public Item {
    public:
    Potion(const Entity::EntityImpl &data); 
    virtual ~Potion() = default;
    virtual char icon() const override;
    virtual void affect(Entity&) override;
};

class HeathPotion: public Potion {
    public:
    HealthPotion(const Entity::EntityImpl &data);
    virtual ~HealthPotion() = default;
    virtual char icon() const override;
    virtual void affect(Entity&) override;
};

#endif
