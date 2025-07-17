export module levelFactory;

export class Level {
    Level(/* ... */); // idk what the params are
    Level(Level &&); // enforced by array
    Level(const Level &);
    Level &operator=(Level &&); // enforced by array, you have to impl
    Level &operator=(const Level &);
};

export class LevelFactory {
    public:
    LevelFactory(std::string name = "default.level");
    Level createLevel();
};
