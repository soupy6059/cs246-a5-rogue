#include "tile.h"

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>
#include <cassert>

#include "item.h"
#include "gold.h"
#include "player.h"

using namespace std;

Tile::Tile(const TileImpl &data):
    data{make_shared<TileImpl>(data)} {}

shared_ptr<Entity> Tile::moveEntity() {
    shared_ptr<Entity> saved = getEntity();
    setEntity(nullptr);
    return saved;
}

shared_ptr<Entity> Tile::getEntity() const {
    return this->data->entity;
}

void Tile::setEntity(shared_ptr<Entity> toEntity) {
    data->entity = toEntity;
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
    case TileType::STAIR:
    case TileType::HALLWAY:
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

void Tile::queryInteraction(Tile &whoFrom) {
     if(!whoFrom.pointingAt(*this)) return;
     // they want to interact with me.

     
     if(shared_ptr<Item> item = dynamic_pointer_cast<Item>(this->getEntity()); item) {
         item->affect(*whoFrom.getEntity());
     }
     else if(shared_ptr<Gold> gold = dynamic_pointer_cast<Gold>(this->getEntity()); gold) {
         if(shared_ptr<DragonHoard> dragonHoard = dynamic_pointer_cast<DragonHoard>(this->getEntity()); dragonHoard) {
             if(dragonHoard->hasDragon()) return;
         }
         // sanity check
         shared_ptr<Player> player = dynamic_pointer_cast<Player>(whoFrom.getEntity());
         assert(player);
         player->setGold(player->getGold() + gold->getValue());
     }
}

void Tile::queryInteraction(Entity &whoFrom) {
    setStatus(Tile::Status{
        .action = Tile::Action::INTERACT,
        .dir = whoFrom.getStatus().dir,
    });
    notifyObservers();
}

void Tile::queryMovement(Entity &whoFrom) {
    setStatus(Tile::Status{
        .action = Tile::Action::MOVE_OWNED_ENTITY,
        .dir = whoFrom.getStatus().dir,
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
    return getRelativeDirection(other) == this->getStatus().dir;
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
        player->setGold(player->getGold() + gold->getValue());
        this->setEntity(nullptr);
    }

    // am i collidable?
    if(isCollidable()) {
        // if i am, do nothing.
        return;
    }
    
    // so they're good to move. im stealing their entity!
    whoFrom.setStatus({
        .action = Tile::Action::SWAP,
        .selfPosition = whoFrom.getPosition(),
        .otherPosition = this->getPosition(),
    });
    whoFrom.notifyObservers();
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

char Tile::icon() const {
    switch(getType()) {
    case TileType::FLOOR:
        return getEntity()? getEntity()->icon() : '.';
    case TileType::STAIR:
        return '/';
    case TileType::HALLWAY:
        return getEntity()? getEntity()->icon() : '#';
    case TileType::DOOR:
        return getEntity()? getEntity()->icon() : '+';
    case TileType::VERTICAL_WALL:
        return '|';
    case TileType::HORIZONTAL_WALL:
        return '-';
    case TileType::VOID:
        return ' ';
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
        case '/':
            return Tile::TileType::STAIR;
        case ' ':
            return Tile::TileType::VOID;
        default:
            return Tile::TileType::FLOOR; // Potentially an entity
    }
}
