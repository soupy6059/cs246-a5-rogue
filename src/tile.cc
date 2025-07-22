#include "tile.h"

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>
#include <cassert>

#include "item.h"

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
    case TileType::WALL:
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
     shared_ptr<Item> item = dynamic_pointer_cast<Item>(this->getEntity());
     if(!item) {
         return; // i don't own an item lol
     }
     item->affect(*whoFrom.getEntity());
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
        return '<';
    case TileType::HALLWAY:
        return getEntity()? getEntity()->icon() : ',';
    case TileType::DOOR:
        return getEntity()? getEntity()->icon() : '/';
    case TileType::WALL:
        return '#';
    case TileType::VOID:
        return ' ';
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
}
