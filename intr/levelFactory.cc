export module levelFactory;

import <memory>;

export class Level {
    std::unique_ptr<Grid> ownedGrid;
    public:
    Level(size_t,size_t); // idk what the params are
    ~Level() = default;
    Level(Level&&); // enforced by array
    Level(const Level&);
    Level &operator=(Level&&); // enforced by array, you have to impl
    Level &operator=(const Level&);
    Grid &getGrid() const;
};

export class LevelFactory {
    public:
    LevelFactory(); // loads "default.level"
    void load(std::string file); // reloads "file"
    Level createLevel();
};
