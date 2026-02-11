#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {

    class Gamestate : public Node {
        GDCLASS(Gamestate, Node)

        private:
            int currentDay;
            int currentTime;
            int currentEnergy;
            // Node* gameHUD;
            Node* energyBarHUD;
            Node* taskListHUD;
            // TODO: list of active tasks. Tasks should probably be a class

        protected:
            static void _bind_methods();

        public:
            Gamestate();
            ~Gamestate();
            void _ready() override;
            void _process(double delta) override;
            void set_current_day(const int p_currentDay);
            int get_current_day() const;
            void set_current_time(const int p_currentTime);
            int get_current_time() const;
            void set_current_energy(const int p_currentEnergy);
            int get_current_energy() const;
    };
}