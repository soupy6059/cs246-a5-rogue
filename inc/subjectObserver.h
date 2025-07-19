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
    protected:
    std::vector<std::shared_ptr<Observer>> &getObservers(); // be careful
    public:
    virtual ~Subject() = default;
    void attach(std::shared_ptr<Observer> obs);
    void notifyObservers();
};

#endif
