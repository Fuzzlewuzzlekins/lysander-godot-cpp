#include "hud.h"
#include "gamestate.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/progress_bar.hpp>

using namespace godot;

void HUD::_bind_methods() {
    // Bind exclusive methods
    // Bind properties and signals
}

HUD::HUD() {
    // Initialize values
    energyBar = nullptr;
    taskList = nullptr;
}

HUD::~HUD() {
    // Cleanup if needed
}

void HUD::_ready() {
    if (!Engine::get_singleton()->is_editor_hint()) {
        // Get key node pointers
        gamestate = get_tree()->get_root()->get_child(0);
        energyBar = find_child("EnergyBar");
        taskList = find_child("TaskList");
        // Update HUD to match Gamestate
        int energy = Object::cast_to<Gamestate>(gamestate)->get_current_energy();
        Object::cast_to<ProgressBar>(energyBar->get_child(0))->set_value(energy);
        Object::cast_to<ProgressBar>(energyBar->get_child(1))->set_value(energy);
    }
}

void HUD::_process(double delta) {
}
