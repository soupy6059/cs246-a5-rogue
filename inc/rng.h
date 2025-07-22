#ifndef __rng__
#define __rng__

class RNGenerator {
    int seed;
    public:

    RNGenerator(int seed = 0);

    // returns lower bound upper inclusive
    void init();
    int getRand(int lower_bound, int upper_bound);
};

#endif