#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

using namespace godot;

void Player::_bind_methods() {
    // Bind getters, setters, and other non-inherited methods here
    ClassDB::bind_method(D_METHOD("_on_animation_finished"), &Player::_on_animation_finished);
    ClassDB::bind_method(D_METHOD("get_entity_speed"), &Player::get_entity_speed);
    ClassDB::bind_method(D_METHOD("set_entity_speed", "p_entSpeed"), &Player::set_entity_speed);
    ClassDB::bind_method(D_METHOD("get_anim_frame_rate"), &Player::get_anim_frame_rate);
    ClassDB::bind_method(D_METHOD("set_anim_frame_rate", "p_animFrameRate"), &Player::set_anim_frame_rate);

    // "Export" gettable/settable properties
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "entSpeed"), "set_entity_speed", "get_entity_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "animFrameRate"), "set_anim_frame_rate", "get_anim_frame_rate");
}

Player::Player() {
    // Initialize values
    entSpeed = 200.0;
    animFrameRate = 10.0;
    // Pixel art settings: 4x scale, nearest
    set_scale(Vector2(4.0,4.0));
    set_texture_filter(TEXTURE_FILTER_NEAREST);
}

Player::~Player() {
    // Cleanup if needed
}

void Player::_ready() {
    // For each animation in SpriteFrames, set FPS
    PackedStringArray sprite_animations = get_sprite_frames()->get_animation_names();
    for (int i=0; i<sprite_animations.size(); i++) {
        get_sprite_frames()->set_animation_speed(sprite_animations[i], animFrameRate);
    }
    set_animation("idle");

    // Create Area2D child
    hitbox = memnew(Area2D);
    CollisionShape2D* hitbox_cshape = memnew(CollisionShape2D);
    RectangleShape2D* hitbox_cshape_rect = memnew(RectangleShape2D);
    hitbox_cshape_rect->set_size(get_sprite_frames()->get_frame_texture("idle", 0)->get_size());
    hitbox_cshape->set_shape(hitbox_cshape_rect);
    hitbox->add_child(hitbox_cshape);
    this->add_child(hitbox);

    // Set up signals
    this->connect("animation_finished", Callable(this, "_on_animation_finished"));
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

void Player::_on_animation_finished() {
    // When the player finishes sitting, they should segue into sit_idle. Same for standing -> idle.
    String currentAnim = get_animation().to_snake_case();
    if (currentAnim == "sit") {
        play("sit_idle");
    } else if (currentAnim == "stand") {
        play("idle");
    }
}

void Player::set_entity_speed(const double p_entSpeed) {
    entSpeed = p_entSpeed;
}

double Player::get_entity_speed() const {
	return entSpeed;
}

void Player::set_anim_frame_rate(const double p_animFrameRate) {
    animFrameRate = p_animFrameRate;
}

double Player::get_anim_frame_rate() const {
    return animFrameRate;
}
