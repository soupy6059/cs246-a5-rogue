module tile;

import <exception>;
import <stdexcept>;
import <string>;

using namespace std;

Tile::Tile(shared_ptr<Entity> entity):
    entity{entity} {}

shared_ptr<Entity> getEntity() const {
    return this->entity;
}

bool isCollidable() {
    switch(this->type) {
    case TileType::FLOOR:
    case TileType::STAIR:
    case TileType::HALLWAY:
    case TileType::DOOR:
        return false;
    case TileType::WALL:
    case TileType::VOID:
        return true;
    default:
       throw out_of_range{"bad enum"};
    }
    throw logic_error{"unreachable"};
}

void Tile::notify(Subject &whoFrom) {
    throw logic_error{"todo"};
}
