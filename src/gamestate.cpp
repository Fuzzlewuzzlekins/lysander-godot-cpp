#include "gamestate.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/progress_bar.hpp>

using namespace godot;

void Gamestate::_bind_methods() {
    // Bind getters, setters, and other non-inherited methods here
    ClassDB::bind_method(D_METHOD("get_current_day"), &Gamestate::get_current_day);
    ClassDB::bind_method(D_METHOD("set_current_day", "p_currentDay"), &Gamestate::set_current_day);
    ClassDB::bind_method(D_METHOD("get_current_time"), &Gamestate::get_current_time);
    ClassDB::bind_method(D_METHOD("set_current_time", "p_currentTime"), &Gamestate::set_current_time);
    ClassDB::bind_method(D_METHOD("get_current_energy"), &Gamestate::get_current_energy);
    ClassDB::bind_method(D_METHOD("set_current_energy", "p_currentEnergy"), &Gamestate::set_current_energy);

    // "Export" gettable/settable properties
    ADD_PROPERTY(PropertyInfo(Variant::INT, "currentDay"), "set_current_day", "get_current_day");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "currentTime"), "set_current_time", "get_current_time");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "currentEnergy"), "set_current_energy", "get_current_energy");
}

Gamestate::Gamestate() {
    currentDay = 0;
    currentTime = 420; // 7 AM
    currentEnergy = 90;
    // gameHUD = nullptr;
    energyBarHUD = nullptr;
    taskListHUD = nullptr;
}

Gamestate::~Gamestate() {
    // Cleanup if needed
}

void Gamestate::_ready() {
    // Declare extra things if needed
    // Find the HUD. It's the second autoload of our project, so it should be at index 1
    // TODO: find a cleaner way to do this? For some reason find_child() isn't working.
    Node* gameHUD = get_tree()->get_root()->get_child(1);
    energyBarHUD = gameHUD->find_child("EnergyBar");
    taskListHUD = gameHUD->find_child("TaskList");
    // Initialize HUD values
    Object::cast_to<ProgressBar>(energyBarHUD)->set_value(currentEnergy);
}

void Gamestate::_process(double delta) {
    // Game loop. Use for special handling if needed

    // // Code below will update energy bar of HUD. TODO: move to appropriate event or signal
    // ProgressBar* energyBar = Object::cast_to<ProgressBar>(gameHUD->get_node_or_null("TopRightPanel/EnergyBar"));
    // energyBar->set_value(currentEnergy);
}

void Gamestate::set_current_day(const int p_currentDay) {
    currentDay = p_currentDay;
}

int Gamestate::get_current_day() const {
	return currentDay;
}

void Gamestate::set_current_time(const int p_currentTime) {
    currentTime = p_currentTime;
}

int Gamestate::get_current_time() const {
	return currentTime;
}

void Gamestate::set_current_energy(const int p_currentEnergy) {
    currentEnergy = p_currentEnergy;
    if (energyBarHUD != nullptr) {
        Object::cast_to<ProgressBar>(energyBarHUD)->set_value(currentEnergy);
    }
}

int Gamestate::get_current_energy() const {
	return currentEnergy;
}
