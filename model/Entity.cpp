#include <Entity.h>

int Entity::id_counter = 0;

EntityType Entity::getType() {
    return type;
}