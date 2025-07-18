export module util;

export enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NORTHEAST,
    SOUTHEAST,
    SOUTHWEST,
    NORTHWEST,
};

export struct Vec2 {
    int x,y;
    Vec2 operator+(const Vec2 &other) const {
        return Vec2{x + other.x, y + other.y};
    }
    Vec2 operator-(const Vec2 &other) const {
        return Vec2{x - other.x, y - other.y};
    }
};
