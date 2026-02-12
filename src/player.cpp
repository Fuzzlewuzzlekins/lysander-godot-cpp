#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>

using namespace godot;

void Player::_bind_methods() {
    // Put Player-unique bindings here. Calling super not needed, throws warnings
    ADD_SIGNAL(MethodInfo("interact", PropertyInfo(Variant::OBJECT, "area")));
    ADD_SIGNAL(MethodInfo("highlight", PropertyInfo(Variant::OBJECT, "area")));
    ADD_SIGNAL(MethodInfo("unhighlight", PropertyInfo(Variant::OBJECT, "area")));
}

Player::Player() {
    closestArea = nullptr;
}

Player::~Player() {
    // Cleanup if needed
}

void Player::_ready() {
    // Trust in parent class Entity's _ready() function (sets up animations and subtree)
    Entity::_ready();

    // Load and bind input actions before the game begins.
    InputMap* inputMap = InputMap::get_singleton();
    inputMap->load_from_project_settings();
}

void Player::_process(double delta) {
    // If player is not sitting or in the process of standing up, they're idle or walking.
    // Continue to choose walk or idle based on input.
    String currentAnim = get_animation().to_snake_case();
    Input* input = Input::get_singleton();
    if (currentAnim != "sit" && currentAnim != "sit_idle" && currentAnim != "stand") {
        // Move left or right if input is exclusive.
        if (input->is_action_pressed("move_left") && !input->is_action_pressed("move_right")) {
            play("walk");
            set_flip_h(true);
            set_position(Vector2(get_position().x - (entSpeed*delta), get_position().y));
        } else if (input->is_action_pressed("move_right") && !input->is_action_pressed("move_left")) {
            play("walk");
            set_flip_h(false);
            set_position(Vector2(get_position().x + (entSpeed*delta), get_position().y));
        } else {
            play("idle");
        }
    }
    // If player is not moving, handle sitting and standing
    if ((input->is_action_pressed("stand_up") || input->is_action_just_pressed("toggle_sit")) && currentAnim == "sit_idle") {
        play("stand");
    }
    if ((input->is_action_pressed("sit_down") || input->is_action_just_pressed("toggle_sit")) && currentAnim == "idle") {
        play("sit");
    }
    // Handle interactions with environment
    TypedArray<Area2D> touchedAreas = hitbox->get_overlapping_areas();
    if (!touchedAreas.is_empty()) {
        // Determine closest overlapping Area2D
        float closest_distance2 = 1000;
        Area2D* new_closest_area;
        for (int i=0; i<touchedAreas.size(); i++) {
            Vector2 myPos = hitbox->get_global_position();
            Area2D* areaChecking = Object::cast_to<Area2D>(touchedAreas[i]);
            float temp_distance2 = myPos.distance_squared_to(areaChecking->get_global_position());
            if (temp_distance2 < closest_distance2) {
                closest_distance2 = temp_distance2;
                new_closest_area = areaChecking;
            }
        }
        // If the closest Area2D has changed, update our pointer and send appropriate signals
        if (closestArea != new_closest_area) {
            emit_signal("highlight", new_closest_area);
            emit_signal("unhighlight", closestArea);
            closestArea = new_closest_area;
        }
        // If the player has pressed Interact, send signal
        if (input->is_action_just_pressed("interact")) {
            emit_signal("interact", closestArea);
        }
    } else {
        // If the player is touching nothing, release not-null pointer (if any) and send signal
        if (closestArea != nullptr) {
            emit_signal("unhighlight", closestArea);
            closestArea = nullptr;
        }
    }
}
