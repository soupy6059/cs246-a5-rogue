#include "item.h"

Item::Item(bool autoPickup):
    Entity{}, autoPickup{autoPickup} {}

char Item::icon() const {
    return 'I';
}
