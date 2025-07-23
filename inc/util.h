#ifndef __util__
#define __util__

#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NORTHEAST,
    SOUTHEAST,
    SOUTHWEST,
    NORTHWEST,
    CENTER,
};

std::string dirToStr(Direction dir);

struct Vec2 {
    int x,y;
    Vec2 operator+(const Vec2 &other) const {
        return Vec2{x + other.x, y + other.y};
    }
    Vec2 operator-(const Vec2 &other) const {
        return Vec2{x - other.x, y - other.y};
    }
    bool operator==(const Vec2 &other) const {
        return x == other.x && y == other.y;
    }
    static Vec2 stepVec(const Vec2 &v, Direction dir) {
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
};

template<typename T> std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);
std::ostream &operator<<(std::ostream &os, const Vec2 &v);
std::ostream &getCout();

struct CharacterDefaults {
    int hp, atk, def, acc, gold;
};

#endif
