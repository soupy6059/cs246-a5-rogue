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
    // each thing that can be pretty printed
    enum class Action {
        SPAWN, ATTACK, MOVE, SEES_POTION, USES_POTION, HOARD_THERE,
    };

    // data and action to send to textDisplay
    struct Status {
        Action action;
        std::variant<
            std::monostate,
            std::shared_ptr<Entity>,
            std::pair<std::shared_ptr<Entity>,Direction>,
            std::pair<std::shared_ptr<Entity>,std::shared_ptr<Entity>>
        > data;
    };

    // list of strings to format then print, decided by the action & status sent
    std::vector<std::string> action;
    Verb &append(std::string);
    void appendStatus(Verb::Status);
};

#endif
