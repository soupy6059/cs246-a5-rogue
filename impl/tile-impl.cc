module tile;

import <exception>;
import <stdexcept>;
import <string>;
import <utility>;

using namespace std;

Tile::Tile(shared_ptr<Entity> entity):
    entity{entity} {}

shared_ptr<Entity> Tile::moveEntity() const {
    return exchange(entity, nullptr);
}

shared_ptr<Entity> Tile::getEntity() const {
    return this->entity;
}

void Tile::setEntity(shared_ptr<Entity> toEntity) const {
    entity = toEntity;
}

const Tile::Status &getStatus() const {
    return *status;
}

void setStatus(const Tile::Status &toStatus) {
    (void)exchange(status, make_shared<Tile::Status>(toStatus));
}

bool Tile::isCollidable() {
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

void queryMovement(Entity &whoFrom) {
    setStatus(Tile::Status::{
        .action = Tile::Status::MOVE_OWNED_ENTITY,
        .dir = whoFrom.getStatus().dir,
    });
    notifyObservers();
}

void notify(Entity &whoFrom) {
    switch(whoFrom.getStatus().action) {
    case Entity::Action::MOVE:
        queryMovement(whoFrom);
        break;
    default:
        throw out_of_range{"bad enum"};
    }
}

bool pointingAt(const Tile &other) const {
    // position

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

void notify(Tile &whoFrom) {
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
        notfiy(dynamic_cast<Entity&>(whoFrom));
    }
    catch(...) {}
    try{
        notify(dynamic_cast<Tile&>(whoFrom));
    }
    catch(...) {}
}

char icon() const {
    switch(this->type) {
    case TileType::FLOOR:
        return entity? entity.icon() : '.';
    case TileType::STAIR:
        return '<';
    case TileType::HALLWAY:
        return entity? entity.icon() : ',';
    case TileType::DOOR:
        return entity? entity.icon() : '/';
    case TileType::WALL:
        return '#';
    case TileType::VOID:
        return ' ';
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
}
