export module game;

import <array>;

import levelFactory;


export class Game {
    LevelFactory levelFactory;
    std::shared_ptr<Entity> player;
    static const std::size_t NUMBER_OF_LEVELS = 5;
    std::array<Level,NUMBER_OF_LEVELS> levels;
    public:
    Game();
    void start();
};
