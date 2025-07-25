#ifndef __potion__
#define __potion__

#include "item.h"
#include <memory>

class Potion: public Item {
    public:
    static const size_t NUMPOTIONTYPES = 6;
    enum PotionType {HEALTH, ATTACK, DEFENSE, POISON, WEAK, BRITTLE};
    Potion(); 
    static std::shared_ptr<Potion> makePotion(PotionType type); // creator for potion
    static void resetKnown(); // reset known's on level reset
    virtual ~Potion() = default;
    virtual std::string icon() const override;
};

class HealthPotion: public Potion {
    static bool known;
    public:
    bool getKnown() const;
    static void setKnown(bool newKnown);
    HealthPotion();
    virtual ~HealthPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class AttackPotion: public Potion {
    static bool known;
    public:
    bool getKnown() const;
    static void setKnown(bool newKnown);
    AttackPotion();
    virtual ~AttackPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class DefensePotion: public Potion {
    static bool known;
    public:
    bool getKnown() const;
    static void setKnown(bool newKnown);
    DefensePotion();
    virtual ~DefensePotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class PoisonPotion: public Potion {
    static bool known;
    public:
    bool getKnown() const;
    static void setKnown(bool newKnown);
    PoisonPotion();
    virtual ~PoisonPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class WeakPotion: public Potion {
    static bool known;
    public:
    bool getKnown() const;
    static void setKnown(bool newKnown);
    WeakPotion();
    virtual ~WeakPotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

class BrittlePotion: public Potion {
    static bool known;
    public:
    bool getKnown() const;
    static void setKnown(bool newKnown);
    BrittlePotion();
    virtual ~BrittlePotion() = default;
    virtual void affect(Entity&) override;
    virtual std::string getName() const override;
};

#endif
