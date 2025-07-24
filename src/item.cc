#include "item.h"

using namespace std;

Item::Item(bool autoPickup):
    Entity{}, autoPickup{autoPickup} {}

string Item::icon() const {
    return "I";
}

void Item::step() {}
