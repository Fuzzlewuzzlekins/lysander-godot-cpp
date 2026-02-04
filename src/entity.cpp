#include "entity.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Entity::_bind_methods() {
    // Bind getters, setters, and other non-inherited methods here
    ClassDB::bind_method(D_METHOD("_on_animation_finished"), &Entity::_on_animation_finished);
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
    // Pixel art settings: 4x scale, nearest
    set_scale(Vector2(4.0,4.0));
    set_texture_filter(TEXTURE_FILTER_NEAREST);
}

Entity::~Entity() {
    // Cleanup if needed
}

void Entity::_ready() {
    // TODO: for each animation in SpriteFrames, set FPS
    // Ref<SpriteFrames> sprite_frames = get_sprite_frames();
    // Having some typing issues here, will reassess later
    set_animation("idle");

    // Set up signals
    this->connect("animation_finished", Callable(this, "_on_animation_finished"));
}

void Entity::_process(double delta) {
    // If player is not sitting or in the process of standing up, they're idle or walking.
    // Continue to choose walk or idle based on input. TODO: replace physical keypresses w/ action mapping
    String currentAnim = get_animation().to_snake_case();
    Input* input = Input::get_singleton();
    if (currentAnim != "sit" && currentAnim != "sit_idle" && currentAnim != "stand") {
        // Move left if input is exclusive. TODO: replace physical keypresses w/ action mapping
        if (input->is_physical_key_pressed(KEY_LEFT) && !input->is_physical_key_pressed(KEY_RIGHT)) {
            play("walk");
            set_flip_h(true);
            set_position(Vector2(get_position().x - (entSpeed*delta), get_position().y));
        } else if (input->is_physical_key_pressed(KEY_RIGHT) && !input->is_physical_key_pressed(KEY_LEFT)) {
            play("walk");
            set_flip_h(false);
            set_position(Vector2(get_position().x + (entSpeed*delta), get_position().y));
        } else {
            play("idle");
        }
    }
    // If player is not moving, handle sitting and standing
    if (input->is_physical_key_pressed(KEY_UP) && currentAnim == "sit_idle") {
        play("stand");
    }
    if (input->is_physical_key_pressed(KEY_DOWN) && currentAnim == "idle") {
        play("sit");
    }

}

void Entity::_on_animation_finished() {
    // When the player finishes sitting, they should segue into sit_idle. Same for standing -> idle.
    String currentAnim = get_animation().to_snake_case();
    if (currentAnim == "sit") {
        play("sit_idle");
    } else if (currentAnim == "stand") {
        play("idle");
    }
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
