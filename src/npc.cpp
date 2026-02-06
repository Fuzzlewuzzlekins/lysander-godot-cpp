#include "npc.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

using namespace godot;

void NPC::_bind_methods() {
    // Bind NPC-specific methods here
}

NPC::NPC() {
    // TBD
    interactible = false;
}

NPC::~NPC() {
    // Cleanup if needed
}

void NPC::_ready() {
    Entity::_ready();
}

void NPC::_process(double delta) {
    // Handle npc behavior... pass in script file? Extend w/ GDScript override?
}