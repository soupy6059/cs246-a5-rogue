#include "rng.h"
#include <cstdlib>
#include <ctime>
#include <memory>

RNGenerator::RNGenerator(int n = 0): seed{n} {srand(n);}

void RNGenerator::init() {
    time_t t;
    time(&t);
    srand(t);
}

int RNGenerator::getRand(int l, int u) {
    int n = rand() % (u - l + 1) + l;
    return n;
}