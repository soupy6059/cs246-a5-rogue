#ifndef __subjectObserver__
#define __subjectObserver__

#include <vector>
#include <memory>

class Subject;

class Observer { 
    public:
    virtual ~Observer() = default;
    virtual void notify(Subject &whoFrom) = 0; 
};

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
    public:
    std::vector<std::shared_ptr<Observer>> &getObservers(); // be careful
    virtual ~Subject() = default;
    void attach(std::shared_ptr<Observer> obs);
    void detach(std::shared_ptr<Observer> obs);
    void detachAll();
    void notifyObservers();
};

#endif
