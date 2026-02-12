#include "npc.h"
#include "gamestate.h"
#include "task.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/callback_tweener.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/classes/interval_tweener.hpp>

using namespace godot;

void NPC::_bind_methods() {
    // Bind NPC-specific methods here
    ClassDB::bind_method(D_METHOD("_on_player_interact", "area"), &NPC::_on_player_interact);
    ClassDB::bind_method(D_METHOD("_on_player_highlight", "area"), &NPC::_on_player_highlight);
    ClassDB::bind_method(D_METHOD("_on_player_unhighlight", "area"), &NPC::_on_player_unhighlight);
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
    if (!Engine::get_singleton()->is_editor_hint()) {
        Entity::_ready();

        // Connect signals of the Player that's been passed to us
        targetPlayer->connect("interact", Callable(this, "_on_player_interact"));
        targetPlayer->connect("highlight", Callable(this, "_on_player_highlight"));
        targetPlayer->connect("unhighlight", Callable(this, "_on_player_unhighlight"));

        // If I have a Task child, hide it on start
        Node* assignment = get_child(0);
        if (assignment != nullptr && assignment->get_class() == "Task") {
            Object::cast_to<Task>(assignment)->hide();
        }
    }
}

void NPC::_process(double delta) {
    // Handle npc behavior... pass in script file? Extend w/ GDScript override?
}

void NPC::_on_player_interact(Area2D* area) {
    // Only run code if MY hitbox is what the Player interacted with
    if (area == hitbox) {
        // Am I the turn-in point for an active Task? check the TaskList
        Node* gameHUD = get_tree()->get_root()->get_child(1);
        Node* taskList = gameHUD->find_child("TaskList");
        for (int i=0; i<taskList->get_child_count(); i++) {
            Task* task = Object::cast_to<Task>(taskList->get_child(i));
            if (task->get_turn_in() == this) {
                // Spend energy to complete the task, if able
                Gamestate* gamestate = Object::cast_to<Gamestate>(get_tree()->get_root()->get_child(0));
                gamestate->set_current_energy(gamestate->get_current_energy() - task->get_energy_cost());
                // Mark the task as complete, then delete
                task->set_pressed(true);
                task->set_disabled(true);
                Ref<Tween> tween = get_tree()->create_tween()->chain();
                tween->tween_interval(0.5);
                tween->tween_property(task, "modulate:a", 0, 1.0);
                tween->tween_callback(Callable(task, "queue_free"));
            }
        }
        // Do I have a Task as a child?
        Node* assignment = get_child(0);
        if (assignment != nullptr && assignment->get_class() == "Task") {
            // Assign task to Player by moving it into the TaskList
            Object::cast_to<Task>(assignment)->show();
            assignment->reparent(taskList, false);
            Ref<Tween> tween = get_tree()->create_tween()->chain();
            tween->tween_property(assignment, "modulate:a", 0, 0.0);
            tween->tween_property(assignment, "modulate:a", 1, 1.0);
        }
    }
}

void NPC::_on_player_highlight(Area2D* area) {
    // Only run code if MY hitbox is what the Player interacted with
    if (area == hitbox) {
        // Animate to show I can be interacted with
        print_line("Gained focus:");
        print_line(this->get_name());
        // Am I the turn-in point for an active Task? check the TaskList
        Node* gameHUD = get_tree()->get_root()->get_child(1);
        Node* taskList = gameHUD->find_child("TaskList");
        for (int i=0; i<taskList->get_child_count(); i++) {
            Task* task = Object::cast_to<Task>(taskList->get_child(i));
            if (task->get_turn_in() == this && task->get_energy_cost() > 0) {
                // TODO: If the task has a cost, flash a warning animation
            }
        }
    }
}

void NPC::_on_player_unhighlight(Area2D* area) {
    // Only run code if MY hitbox is what the Player interacted with
    if (area == hitbox) {
        print_line("Lost focus:");
        print_line(this->get_name());
        // TODO: stop the task cost warning animation, if applicable. See above
    }
}

void NPC::set_target_player(Player* p_player) {
    targetPlayer = p_player;
}

Player* NPC::get_target_player() const {
	return targetPlayer;
}
