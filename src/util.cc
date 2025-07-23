#include "util.h"

using namespace std;

ostream &getCout() { return cout; }

ostream &operator<<(ostream &os, const Vec2 &v) {
    os << "[" << v.x << "," << v.y << "]";
    return os;
}

string dirToStr(Direction dir) {
    switch(dir) {
        case Direction::NORTH: return "North";
        case Direction::SOUTH: return "South";
        case Direction::EAST: return "East";
        case Direction::WEST: return "West";
        case Direction::NORTHEAST: return "Northeast";
        case Direction::SOUTHEAST: return "Southeast";
        case Direction::SOUTHWEST: return "Southwest";
        case Direction::NORTHWEST: return "Northwest";
        case Direction::CENTER: return "Center";
    default:
        throw logic_error{"bad enum"};
    }
    throw logic_error{"unreachable"};
};

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for(size_t i{0}; i < v.size(); ++i) {
        os << v.at(i);
        if(i < v.size() - 1) os << ", ";
    }
    return os << "]";
}
