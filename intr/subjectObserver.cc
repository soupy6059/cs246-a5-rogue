export module subjectObserver;

import <vector>;
import <memory>;

export class Subject;

export class Observer { 
    public:
    virtual ~Observer() = default;
    virtual void notify(Subject &whoFrom) = 0; 
};

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
    protected:
    std::vector<std::shared_ptr<Observer>> &getObservers(); // be careful
    public:
    void attach(std::shared_ptr<Observer> obs);
    void notifyObservers();
};
