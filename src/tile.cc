#include "tile.h"

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>
#include <cassert>

#include "item.h"
#include "verb.h"
#include "gold.h"
#include "player.h"
#include "potion.h"
#include "races.h"

using namespace std;

Tile::Tile(const TileImpl &data):
    data{make_shared<TileImpl>(data)} {}

shared_ptr<Entity> Tile::moveEntity() {
    shared_ptr<Entity> saved = getEntity();
    data->entity = data->goldStorage;
    data->goldStorage = nullptr;
    return saved;
}

shared_ptr<Entity> Tile::getEntity() const {
    return this->data->entity;
}

// small vector?
// 
// override on not gold,
// push on gold
//
// on move,
// if gold, nothing -> nothing | gold
// if entity, nothing -> nothing | entity
// if entity, gold -> gold | entity

void Tile::setEntity(shared_ptr<Entity> toEntity) {
    if(dynamic_pointer_cast<Gold>(toEntity) && dynamic_pointer_cast<Gold>(data->entity)) {
        throw logic_error{"spawing double gold"};
    }

    if(!toEntity) {
        if(dynamic_pointer_cast<Merchant>(getEntity())) {
            data->entity = make_shared<Gold>(4);
        } else if(dynamic_pointer_cast<Human>(getEntity())) {
            data->entity = make_shared<Gold>(2); 
            for(auto observer: getObservers()) {
                if(auto tile = dynamic_pointer_cast<Tile>(observer); tile) {
                    if(tile->getEntity() == nullptr) {
                        tile->setEntity(make_shared<Gold>(2));
                        break;
                    }
                }
            }
        } else data->entity = data->goldStorage;
        return;
    }

    if(dynamic_pointer_cast<Gold>(data->entity)) {
        data->goldStorage = data->entity;
        data->entity = toEntity;
    } else {
        data->entity = toEntity;
    }
}


void Tile::swapTileEntities(Tile &a, Tile &b) {
    swap(a.data->entity,b.data->entity);
}

const Tile::Status &Tile::getStatus() const {
    return data->status;
}

void Tile::setStatus(const Tile::Status &toStatus) {
    data->status = toStatus;
}

const Tile::TileType &Tile::getType() const {
    return data->type;
}

void Tile::setType(const TileType &toType) {
    data->type = toType;
}

bool Tile::isCollidable() const {
    switch(getType()) {
    case TileType::FLOOR:
    case TileType::HALLWAY:
    case TileType::STAIR:
    case TileType::DOOR:
        return getEntity()? true : false;
    case TileType::HORIZONTAL_WALL:
    case TileType::VERTICAL_WALL:
    case TileType::VOID:
        return true;
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
}

bool Tile::isFloor() const {
    return getType() == TileType::FLOOR;
}

void Tile::queryInteraction(Tile &whoFrom) {
     if(!whoFrom.pointingAt(*this)) return;
     // they want to interact with me.

     
     if(shared_ptr<Item> item = dynamic_pointer_cast<Item>(this->getEntity()); item) {
         item->affect(*whoFrom.getEntity());
     }
}

void Tile::queryInteraction(Entity &whoFrom) {
    setStatus(Tile::Status{
        .action = Tile::Action::INTERACT,
        .data = get<Direction>(whoFrom.getStatus().data),
    });
    notifyObservers();
}

void Tile::queryMovement(Entity &whoFrom) {
    setStatus(Tile::Status{
        .action = Tile::Action::MOVE_OWNED_ENTITY,
        .data = get<Direction>(whoFrom.getStatus().data),
    });
    notifyObservers();
}

void Tile::notify(Entity &whoFrom) {
    switch(whoFrom.getStatus().action) {
    case Entity::Action::MOVE:
        queryMovement(whoFrom);
        break;
    case Entity::Action::INTERACT:
        queryInteraction(whoFrom);
        break;
    case Entity::Action::KILL_ME:
        setEntity(nullptr);
        break;
    case Entity::Action::ATTACK:
        setStatus({
            .action = Tile::Action::ATTACK,
            .data = get<Direction>(whoFrom.getStatus().data),
        });
        notifyObservers();
        break;
    case Entity::Action::PRINT_LEVEL:
    case Entity::Action::RESTART:
    case Entity::Action::QUIT:
        break;
    default:
        throw out_of_range{"bad enum"};
    }
}

const vector<Direction> &iotaDirection() {
    static const vector<Direction> dirs { 
        Direction::NORTHWEST,
        Direction::NORTH,
        Direction::NORTHEAST,
        Direction::WEST,
        Direction::EAST,
        Direction::SOUTHWEST,
        Direction::SOUTH,
        Direction::SOUTHEAST,
    };
    return dirs;
}


const Vec2 &Tile::getPosition() const {
    return data->position;
}

void Tile::setPosition(const Vec2 &newPosition) {
    data->position = newPosition;
}

Direction Tile::getRelativeDirection(const Tile &other) const {
    for(const auto &dir : iotaDirection()) {
        if(Vec2::stepVec(getPosition(), dir) == other.getPosition()) return dir;
    }
    throw logic_error{"unreachable"};
}

bool Tile::pointingAt(const Tile &other) const {
    return getRelativeDirection(other) == get<Direction>(this->getStatus().data);
}

void Tile::queryMovement(Tile &whoFrom) {
    // so a tile wants to move.
    if(!whoFrom.pointingAt(*this)) return;
    // so a tile wants to move, to me!

    // YAY HERES A SUPER SPECIFIC CASE!!!!
    // if(whoFrom.getEntity() is Player && this->getEntity() is Gold) {
    //     player.setGold(player->getGold() + gold->getValue());
    //     this->setEntity(nullptr); // kill gold
    // }
    shared_ptr<Player> player = dynamic_pointer_cast<Player>(whoFrom.getEntity());
    shared_ptr<Gold> gold = dynamic_pointer_cast<Gold>(this->getEntity());
    if(player && gold) {
        if(auto dragonHoard = dynamic_pointer_cast<DragonHoard>(gold); dragonHoard) {
            if(!dragonHoard->hasDragon()) {
                player->setGold(player->getGold() + gold->getValue());
                this->setEntity(nullptr);
            }
        } else {
            player->setGold(player->getGold() + gold->getValue());
            this->setEntity(nullptr);
        }
    }

    if(!player && (getType() == Tile::TileType::STAIR || getType() == Tile::TileType::DOOR)) return;

    // am i collidable?
    if(isCollidable()) {
        // if i am, do nothing.
        return;
    }

    // doubleRisk management
    switch(get<Direction>(whoFrom.getStatus().data)) {
        case Direction::SOUTHWEST:
        case Direction::SOUTH:
        case Direction::SOUTHEAST:
        case Direction::EAST:
            if (!whoFrom.getEntity()) return;
            whoFrom.getEntity()->setDoubleRisk(true);
        default:
            break;
    }

    // print MOVEMENT
    if(player) {
        player->appendVerb(Verb::Status{
            .action = Verb::Action::MOVE,
            .data = pair<shared_ptr<Entity>,Direction>(
                player,
                get<Direction>(player->getStatus().data)
            ), 
        });
    }

    // so they're good to move. im stealing their entity!
    whoFrom.setStatus({
        .action = Tile::Action::SWAP,
        .data = pair<Vec2,Vec2>(whoFrom.getPosition(),this->getPosition()),
    });
    whoFrom.notifyObservers();
    setStatus({.action = Tile::Action::ADJACENT_POTION, .data = monostate{}});
    notifyObservers();
}

void Tile::queryPotion(Tile &whoFrom) {
    if(!dynamic_pointer_cast<Player>(whoFrom.getEntity())) return;
    if(!dynamic_pointer_cast<Potion>(getEntity())) return;
    auto player = dynamic_pointer_cast<Player>(whoFrom.getEntity());
    auto potionPtr {dynamic_pointer_cast<Potion>(getEntity())};
    player->appendVerb({
        .action = Verb::Action::SEES_POTION,
        .data = pair<shared_ptr<Entity>,shared_ptr<Entity>>(player,potionPtr),
    });
}

void Tile::queryAttack(Tile &whoFrom) {
     if(!whoFrom.pointingAt(*this)) return;
     // they want to interact with me.
     
     if(!dynamic_pointer_cast<Character>(getEntity())) {
         return;
     }

     // verbAppend <=> action pretty printing
     auto player = dynamic_pointer_cast<Player>(whoFrom.getEntity());
     auto target = dynamic_pointer_cast<Character>(this->getEntity());

     dynamic_pointer_cast<Character>(whoFrom.getEntity())->attack(*this);
     if(player && target) {
         player->appendVerb({Verb::Action::ATTACK,pair<shared_ptr<Entity>,shared_ptr<Entity>>(player,target)});
     }
}

void Tile::notify(Tile &whoFrom) {
    switch(whoFrom.getStatus().action) {
    case Tile::Action::MOVE_OWNED_ENTITY:
        queryMovement(whoFrom);
        break;
    case Tile::Action::SWAP:
        break;
    case Tile::Action::INTERACT:
        queryInteraction(whoFrom);
        break;
    case Tile::Action::ADJACENT_POTION:
        queryPotion(whoFrom);
        break;
    case Tile::Action::ATTACK:
        queryAttack(whoFrom);
        break;
    default:
        throw out_of_range{"bad enum"};
    }
}

void Tile::notify(Subject &whoFrom) {
    try {
        notify(dynamic_cast<Entity&>(whoFrom));
    }
    catch(...) {}
    try{
        notify(dynamic_cast<Tile&>(whoFrom));
    }
    catch(...) {}
}

string Tile::icon() const {
    switch(getType()) {
    case TileType::FLOOR:
        return getEntity()? getEntity()->icon() : ".";
    case TileType::STAIR:
        return "\033[94;1m\\\033[0m";
    case TileType::HALLWAY:
        return getEntity()? getEntity()->icon() : "#";
    case TileType::DOOR:
        return getEntity()? getEntity()->icon() : "+";
    case TileType::VERTICAL_WALL:
        return "|";
    case TileType::HORIZONTAL_WALL:
        return "-";
    case TileType::VOID:
        return " ";
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
}

Tile::TileType fromChar(char c) {
    switch (c) {
        case '.': 
            return Tile::TileType::FLOOR;
        case '|':
            return Tile::TileType::VERTICAL_WALL;
        case '-': 
            return Tile::TileType::HORIZONTAL_WALL;
        case '#':
            return Tile::TileType::HALLWAY;
        case '+':
            return Tile::TileType::DOOR;
        case '\\':
            return Tile::TileType::STAIR;
        case ' ':
            return Tile::TileType::VOID;
        default:
            return Tile::TileType::FLOOR; // Potentially an entity
    }
}
