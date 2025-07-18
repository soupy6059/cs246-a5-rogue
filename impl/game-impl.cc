module game;

using namespace std;

// static const std::size_t NUMBER_OF_LEVELS = 5;

// export class Game {
//     LevelFactory levelFactory;
//     std::shared_ptr<Entity> player;
//     std::array<Level,NUMBER_OF_LEVELS> levels;
//     public:
//     Game();
//     void start();
// };

Game::Game():
    levelFactory{},
    player{nullptr},
    levels{} {
    for(size_t i{0}; i < levels.size(); ++i) {
        levels.at(i) = levelFactory.create();
    }
}
