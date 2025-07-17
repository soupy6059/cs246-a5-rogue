export module game;

import <array>;

import levelFactory;

export class Game {
    LevelFactory levelFactory;
    static const std::size_t NUMBER_OF_LEVELS = 5;
    std::array<Level,NUMBER_OF_LEVELS> levels;
    public:
    void start();
};
