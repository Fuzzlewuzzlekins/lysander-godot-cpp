#pragma once

#include <godot_cpp/classes/check_box.hpp>

namespace godot {

    class Task : public CheckBox {
        GDCLASS(Task, CheckBox)

        private:
            // member vars
            int timeCost;
            int energyCost;
            Node* turnIn;

        protected:
            static void _bind_methods();
        
        public:
            Task();
            ~Task();
            void _ready() override;
            void _process(double delta) override;
            // getters/setters for member vars
            void set_time_cost(const int p_timeCost);
            int get_time_cost() const;
            void set_energy_cost(const int p_energyCost);
            int get_energy_cost() const;
            void set_turn_in(Node* p_turnIn);
            Node* get_turn_in() const;
    };
}