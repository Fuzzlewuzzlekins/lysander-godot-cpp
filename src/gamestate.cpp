#include "gamestate.h"

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
}

Gamestate::~Gamestate() {
    // Cleanup if needed
}

void Gamestate::_ready() {
    // Declare extra things if needed
}

void Gamestate::_process(double delta) {
    // Game loop. Use for special handling if needed
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
}

int Gamestate::get_current_energy() const {
	return currentEnergy;
}
