# Design Document for Rogue

// manages the neighbours of it's subjects.
struct Universe: public Observer {
};

struct Group {
    vector<unique_ptr<Entity>> members;
};

class GroundedSubject: public Subject {
    Observer *universe;
    public:
    GroundedSubject(Observer *universe): Subject{}, universe{universe} {}
    virtual void notifyObservers() override {
        universe->notify(*this); // universe manages *this's entities
        for(auto &ob: observers)
            ob->notify(*this);
    }
};

class Entity:
    public Observer, public GroundedSubject, public Decorator {
    // ...
};

for(const unique_ptr<Entity>& currentEntity: universe) {
    // can only effect it's neighbours.
    currentEntity->update();          // change own state
    currentEntity->notifyObservers(); // notify neighbours of state
}

/*
an entity has to live in a universe.
// maybe another type of subject?
// 

entity: in universe.
entity moves.
notifies observers.
UNIVERSE IS TOLD FIRST.
universe changes it's neighbours.

*/
