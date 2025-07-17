module subjectObserver;

using namespace std;

void Subject::attach(shared_ptr<Observer> obs) {
    this->observers.push_back(obs);
    return;
}

void Subject::notifyObservers() {
    for(shared_ptr<Observer> obs: this->observers) {
        obs->notify(*this);
    }
    return;
}
