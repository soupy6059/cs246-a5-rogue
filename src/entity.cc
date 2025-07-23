#include "entity.h"

#include <memory>

using namespace std;

Entity::Entity(const Entity::EntityImpl &data):
    Subject{}, data{new EntityImpl{data}} {}

Entity::EntityImpl &Entity::getStats() const {
    return *data;
}

const Entity::Status &Entity::getStatus() {
    return data->status;
}


void Entity::setStatus(const Status &newStatus) {
    data->status = newStatus; 
}

void Entity::mainUpdate() {
    step();
}

void Entity::update() {
    mainUpdate();
}

bool Entity::getDoubleRisk() {
    return data->doubleRisk;
}

void Entity::setDoubleRisk(bool newRisk) {
    data->doubleRisk = newRisk;
}

Entity::Entity(const Entity &other):
    Subject{}, data{new EntityImpl{*other.data}} {}

Entity::Entity(Entity &&other):
    Subject{}, data{move(other.data)} {}

Entity &Entity::operator=(const Entity &other) {
    data = unique_ptr<EntityImpl>{new EntityImpl{*other.data}};
    return *this;
}

Entity &Entity::operator=(Entity &&other) {
    swap(data, other.data);
    return *this;
}


