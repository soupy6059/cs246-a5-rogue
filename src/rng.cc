#include "rng.h"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <cassert>

int getRand(int l, int u) {
    assert(u >= l);
    return (rand() % (u - l)) + l;
}

size_t getRand(size_t l, size_t u) {
    assert(u >= l);
    return static_cast<size_t>((rand() % (u - l)) + l);
}

void initRand(int seed) {
    srand(seed);
}
