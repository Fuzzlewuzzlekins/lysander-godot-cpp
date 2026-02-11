#include "task.h"

using namespace godot;

void Task::_bind_methods() {
    // Bind unique methods
    ClassDB::bind_method(D_METHOD("get_time_cost"), &Task::get_time_cost);
    ClassDB::bind_method(D_METHOD("set_time_cost", "p_timeCost"), &Task::set_time_cost);
    ClassDB::bind_method(D_METHOD("get_energy_cost"), &Task::get_energy_cost);
    ClassDB::bind_method(D_METHOD("set_energy_cost", "p_energyCost"), &Task::set_energy_cost);
    ClassDB::bind_method(D_METHOD("get_turn_in"), &Task::get_turn_in);
    ClassDB::bind_method(D_METHOD("set_turn_in", "p_turnIn"), &Task::set_turn_in);
    // Export properties
    ADD_PROPERTY(PropertyInfo(Variant::INT, "timeCost"), "set_time_cost", "get_time_cost");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "energyCost", PROPERTY_HINT_RANGE, "0,100,1"), "set_energy_cost", "get_energy_cost");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "turnIn", PROPERTY_HINT_NODE_TYPE, "Node"), "set_turn_in", "get_turn_in");
}

Task::Task() {
    // Initialize values
    timeCost = 10;
    energyCost = 10;
    turnIn = nullptr;
    // Configure CheckBox behavior (word wrap, not clickable)
    set_text("Complete task");
    set_autowrap_mode(TextServer::AUTOWRAP_WORD_SMART);
    set_button_mask(BitField<MouseButtonMask>(MOUSE_BUTTON_NONE));
    set_pressed(false);
}

Task::~Task() {
    // Clean up if needed
}

void Task::_ready() {
    // Set up in scene
}

void Task::_process(double delta) {
    // To be determined...
}

void Task::set_time_cost(const int p_timeCost) {
    timeCost = p_timeCost;
}

int Task::get_time_cost() const {
	return timeCost;
}

void Task::set_energy_cost(const int p_energyCost) {
    energyCost = p_energyCost;
}

int Task::get_energy_cost() const {
	return energyCost;
}

void Task::set_turn_in(Node *p_turnIn) {
    turnIn = p_turnIn;
}

Node *Task::get_turn_in() const {
	return turnIn;
}
