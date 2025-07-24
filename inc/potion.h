#ifndef __potion__
#define __potion__

#include "item.h"
#include <memory>

class Potion: public Item {
    public:
    static const size_t NUMPOTIONTYPES = 6;
    enum PotionType {HEALTH, ATTACK, DEFENSE, POISON, WEAK, BRITTLE};
    Potion(); 
    static std::shared_ptr<Potion> makePotion(PotionType type);
    virtual ~Potion() = default;
    virtual std::string icon() const override;
};

class HealthPotion: public Potion {
    public:
    HealthPotion();
    virtual ~HealthPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class AttackPotion: public Potion {
    public:
    AttackPotion();
    virtual ~AttackPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class DefensePotion: public Potion {
    public:
    DefensePotion();
    virtual ~DefensePotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class PoisonPotion: public Potion {
    public:
    PoisonPotion();
    virtual ~PoisonPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class WeakPotion: public Potion {
    public:
    WeakPotion();
    virtual ~WeakPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class BrittlePotion: public Potion {
    public:
    BrittlePotion();
    virtual ~BrittlePotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

#endif
