#include "tile.h"

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>
#include <cassert>

using namespace std;

Tile::Tile(shared_ptr<Entity> entity):
    entity{entity} {}

shared_ptr<Entity> Tile::moveEntity() const {
    shared_ptr<Entity> saved = move(entity);
    assert(entity == nullptr);
    return saved;
}

shared_ptr<Entity> Tile::getEntity() const {
    return this->entity;
}

void Tile::setEntity(shared_ptr<Entity> toEntity) {
    entity = toEntity;
}

const Tile::Status &Tile::getStatus() const {
    return *status;
}

void Tile::setStatus(const Tile::Status &toStatus) {
    status = shared_ptr<Tile::Status>{new Tile::Status{toStatus}};
}

bool Tile::isCollidable() const {
    switch(this->type) {
    case TileType::FLOOR:
    case TileType::STAIR:
    case TileType::HALLWAY:
    case TileType::DOOR:
        return this->entity? true : false;
    case TileType::WALL:
    case TileType::VOID:
        return true;
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
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

Direction Tile::getRelativeDirection(const Tile &other) const {
    for(const auto &dir : iotaDirection()) {
        if(Vec2::step(*position, dir) == *other.position) return dir;
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
    setEntity(whoFrom.moveEntity()); // done!
}

void Tile::notify(Tile &whoFrom) {
    switch(whoFrom.getStatus().action) {
    case Tile::Action::MOVE_OWNED_ENTITY:
        queryMovement(whoFrom);
        break;
    default:
        throw out_of_range{"bad enum"};
    }
}

void Tile::notify(Subject &whoFrom) {
    // the "what is notifying me" function

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
    switch(this->type) {
    case TileType::FLOOR:
        return entity? entity->icon() : '.';
    case TileType::STAIR:
        return '<';
    case TileType::HALLWAY:
        return entity? entity->icon() : ',';
    case TileType::DOOR:
        return entity? entity->icon() : '/';
    case TileType::WALL:
        return '#';
    case TileType::VOID:
        return ' ';
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
}
