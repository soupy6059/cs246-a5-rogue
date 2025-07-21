#include "util.h"

using namespace std;

ostream &getCout() { return cout; }

ostream &operator<<(ostream &os, const Vec2 &v) {
    os << "[" << v.x << "," << v.y << "]";
    return os;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for(size_t i{0}; i < v.size(); ++i) {
        os << v.at(i);
        if(i < v.size() - 1) os << ", ";
    }
    return os << "]";
}
