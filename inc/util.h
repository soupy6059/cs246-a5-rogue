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

Direction clockwise(Direction dir); // rotates a direction 45 deg clockwise

struct Vec2 {
    int x,y;

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    bool operator==(const Vec2 &other) const;

    // moves a vector in a direction, by copy
    static Vec2 stepVec(const Vec2 &v, Direction dir);
};

template<typename T> std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);
std::ostream &operator<<(std::ostream &os, const Vec2 &v);
std::ostream &getCout();

struct CharacterDefaults {
    int hp, atk, def, acc, gold;
};

#endif
