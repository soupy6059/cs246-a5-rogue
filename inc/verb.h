#ifndef __verb__
#define __verb__

#include <vector>
#include <variant>
#include <tuple>
#include <string>
#include <memory>
#include <utility>

#include "entity.h"

class Verb {
public:
    enum class Action {
        SPAWN, ATTACK, MOVE, SEES_POTION, USES_POTION,
    };
    struct Status {
        Action action;
        std::variant<
            std::monostate,
            std::shared_ptr<Entity>,
            std::pair<std::shared_ptr<Entity>,Direction>,
            std::pair<std::shared_ptr<Entity>,std::shared_ptr<Entity>>
        > data;
    };
    bool empty = true;
    std::vector<std::string> action;
    Verb &append(std::string);
    void appendStatus(Verb::Status);
};

#endif
