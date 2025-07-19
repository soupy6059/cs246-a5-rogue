#include "entity.h"

#include <memory>

using namespace std;

Entity::Entity(const Entity::EntityImpl &data):
    data{new EntityImpl{data}} {}

Entity::EntityImpl &Entity::getStats() const {
    return *data;
}

const Entity::Status &Entity::getStatus() {
    return data->status;
}

void Entity::mainUpdate() {
    step();
}

void Entity::update() {
    mainUpdate();
}

Entity::Entity(const Entity &other):
    data{new EntityImpl{*other.data}} {}

Entity::Entity(Entity &&other):
    data{move(other.data)} {}

Entity &Entity::operator=(const Entity &other) {
    data = unique_ptr<EntityImpl>{new EntityImpl{*other.data}};
    return *this;
}

Entity &Entity::operator=(Entity &&other) {
    swap(data, other.data);
    return *this;
}


