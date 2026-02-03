#include "entity.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Entity::_bind_methods() {
    // Bind getters, setters, and other non-inherited methods here
    ClassDB::bind_method(D_METHOD("get_entity_speed"), &Entity::get_entity_speed);
    ClassDB::bind_method(D_METHOD("set_entity_speed", "p_entSpeed"), &Entity::set_entity_speed);
    ClassDB::bind_method(D_METHOD("get_anim_frame_rate"), &Entity::get_anim_frame_rate);
    ClassDB::bind_method(D_METHOD("set_anim_frame_rate", "p_animFrameRate"), &Entity::set_anim_frame_rate);

    // "Export" gettable/settable properties
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "entSpeed"), "set_entity_speed", "get_entity_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "animFrameRate"), "set_anim_frame_rate", "get_anim_frame_rate");
}

Entity::Entity() {
    // Initialize values
    entSpeed = 200.0;
    animFrameRate = 10.0;
}

Entity::~Entity() {
    // Cleanup if needed
}

void Entity::_ready() {
    // TODO: for each animation in SpriteFrames, set FPS
}

void Entity::_process(double delta) {
    // Do Godot loop stuff. TODO: movement and animation logic
}

void Entity::set_entity_speed(const double p_entSpeed) {
    entSpeed = p_entSpeed;
}

double Entity::get_entity_speed() const {
	return entSpeed;
}

void Entity::set_anim_frame_rate(const double p_animFrameRate) {
    animFrameRate = p_animFrameRate;
}

double Entity::get_anim_frame_rate() const {
    return animFrameRate;
}
