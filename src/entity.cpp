#include "entity.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

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
    // queue_free();
}

void Entity::_ready() {
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

void Entity::_process(double delta) {
    // Entity's behavior will be coded here. Abstracted out to subclasses Player and NPC.
}

void Entity::_on_animation_finished() {
    // When the entity finishes sitting, they should segue into sit_idle. Same for standing -> idle.
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
