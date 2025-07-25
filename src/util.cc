#include "util.h"

using namespace std;

ostream &getCout() { return cout; }

ostream &operator<<(ostream &os, const Vec2 &v) {
    os << "[" << v.x << "," << v.y << "]";
    return os;
}

Direction clockwise(Direction dir) {
    switch(dir) {
        case Direction::NORTH: return Direction::NORTHEAST;
        case Direction::SOUTH: return Direction::SOUTHWEST;
        case Direction::EAST: return Direction::SOUTHEAST;
        case Direction::WEST: return Direction::NORTHWEST;
        case Direction::NORTHEAST: return Direction::EAST;
        case Direction::SOUTHEAST: return Direction::SOUTH;
        case Direction::SOUTHWEST: return Direction::WEST;
        case Direction::NORTHWEST: return Direction::NORTH;
        case Direction::CENTER: return Direction::CENTER;
    default:
        throw logic_error{"bad enum"};
    }
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


Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2{x + other.x, y + other.y};
}
Vec2 Vec2::operator-(const Vec2 &other) const {
    return Vec2{x - other.x, y - other.y};
}
bool Vec2::operator==(const Vec2 &other) const {
    return x == other.x && y == other.y;
}


Vec2 Vec2::stepVec(const Vec2 &v, Direction dir) {
    switch(dir) {
    case Direction::NORTH:     return v + Vec2{-1, 0};
    case Direction::SOUTH:     return v + Vec2{ 1, 0};
    case Direction::EAST:      return v + Vec2{ 0, 1};
    case Direction::WEST:      return v + Vec2{ 0,-1};
    case Direction::NORTHEAST: return v + Vec2{-1, 1};
    case Direction::SOUTHEAST: return v + Vec2{ 1, 1};
    case Direction::SOUTHWEST: return v + Vec2{ 1,-1};
    case Direction::NORTHWEST: return v + Vec2{-1,-1};
    case Direction::CENTER:    return v + Vec2{ 0, 0};
    default: throw std::out_of_range{"bad enum"};
    }
    throw std::logic_error{"unreachable"};
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
