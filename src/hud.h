#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>

namespace godot {

    class HUD : public CanvasLayer {
        GDCLASS(HUD, CanvasLayer)

        private:
            // member vars
            Node* gamestate;
            Node* energyBar;
            Node* taskList;

        protected:
            static void _bind_methods();

        public:
            HUD();
            ~HUD();
            void _ready() override;
            void _process(double delta) override;
            // getters/setters for member vars
    };
}