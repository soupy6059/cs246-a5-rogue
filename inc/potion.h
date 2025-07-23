#ifndef __potion__
#define __potion__

#include "item.h"
#include <memory>

class Potion: public Item {
    public:
    enum PotionType {HEALTH, ATTACK, DEFENSE, POISON, WEAK, BRITTLE};
    Potion(const Entity::EntityImpl &data); 
    std::unique_ptr<Potion> makePotion(PotionType type);
    virtual ~Potion() = default;
    virtual char icon() const override;
    virtual void affect(Entity&) override;
};

class HealthPotion: public Potion {
    public:
    HealthPotion(const Entity::EntityImpl &data);
    virtual ~HealthPotion() = default;
    virtual void affect(Entity&) override;
};

class AttackPotion: public Potion {
    public:
    AttackPotion(const Entity::EntityImpl &data);
    virtual ~AttackPotion() = default;
    virtual void affect(Entity&) override;
};

class DefensePotion: public Potion {
    public:
    DefensePotion(const Entity::EntityImpl &data);
    virtual ~DefensePotion() = default;
    virtual void affect(Entity&) override;
};

class PoisonPotion: public Potion {
    public:
    PoisonPotion(const Entity::EntityImpl &data);
    virtual ~PoisonPotion() = default;
    virtual void affect(Entity&) override;
};

class WeakPotion: public Potion {
    public:
    WeakPotion(const Entity::EntityImpl &data);
    virtual ~WeakPotion() = default;
    virtual void affect(Entity&) override;
};

class BrittlePotion: public Potion {
    public:
    BrittlePotion(const Entity::EntityImpl &data);
    virtual ~BrittlePotion() = default;
    virtual void affect(Entity&) override;
};

#endif
