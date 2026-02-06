#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Player::_bind_methods() {
    // Put Player-unique bindings here. Calling super not needed, throws warnings
}

Player::Player() {
    // Does anything need to be done here? Calling super makes Godot crash
}

Player::~Player() {
    // Cleanup if needed
}

void Player::_ready() {
    // Trust in parent class Entity's _ready() function (sets up animations and subtree)
    Entity::_ready();
}

void Player::_process(double delta) {
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
