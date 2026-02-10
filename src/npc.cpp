#include "npc.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

using namespace godot;

void NPC::_bind_methods() {
    // Bind NPC-specific methods here
    ClassDB::bind_method(D_METHOD("_on_player_interact", "closest_area"), &NPC::_on_player_interact);
    ClassDB::bind_method(D_METHOD("get_target_player"), &NPC::get_target_player);
    ClassDB::bind_method(D_METHOD("set_target_player", "p_player"), &NPC::set_target_player);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "targetPlayer", PROPERTY_HINT_NODE_TYPE, "Player"), "set_target_player", "get_target_player");
}

NPC::NPC() {
    // Initialize values
    interactible = false;
    targetPlayer = nullptr;
}

NPC::~NPC() {
    // Cleanup if needed
}

void NPC::_ready() {
    Entity::_ready();

    // Connect "interact" signal of the Player that's been passed to us
    targetPlayer->connect("interact", Callable(this, "_on_player_interact"));
}

void NPC::_process(double delta) {
    // Handle npc behavior... pass in script file? Extend w/ GDScript override?
}

void NPC::_on_player_interact(Area2D* closest_area) {
    // Only run code if MY hitbox is what the Player interacted with
    if (closest_area == hitbox) {
        print_line("Interacted with " + this->get_name());
    }
}

void NPC::set_target_player(Player* p_player) {
    targetPlayer = p_player;
}

Player* NPC::get_target_player() const {
	return targetPlayer;
}
