module entity;

Entity::Entity(const Entity::EntityImpl &data):
    data{new EntityImpl{ // struct enables aggregate init, & "new" b/c uptr allows it
        .stats = {0, 0, 0},
    }} {}

Entity::EntityImpl &Entity::getStats() const {
    return *data;
}

void Entity::mainUpdate() {
    step();
}

void Entity::update() {
    mainUpdate();
}
