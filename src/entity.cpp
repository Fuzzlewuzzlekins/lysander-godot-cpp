#include "entity.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Entity::_bind_methods() {
    // Bind getters, setters, and other non-inherited methods here
    // ClassDB::bind_method(D_METHOD("greturn_method_name"), &Entity::greturn_method_name);
    // ClassDB::bind_method(D_METHOD("svoid_method_name", "p_parameter"), &Entity::svoid_method_name);

    // "Export" gettable/settable properties
    // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "property_name"), "svoid_method_name", "greturn_method_name");
}

Entity::Entity() {
    // Initialize values
}

Entity::~Entity() {
    // Cleanup if needed
}

void Entity::_process(double delta) {
    // Do Godot loop stuff. Does not need to go in _bind_methods()
}

