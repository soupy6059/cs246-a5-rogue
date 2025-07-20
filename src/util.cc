#include "util.h"

std::ostream &getCout() { return std::cout; }

std::ostream &operator<<(std::ostream &os, const Vec2 &v) {
    os << "[" << v.x << "," << v.y << "]";
    return os;
}
