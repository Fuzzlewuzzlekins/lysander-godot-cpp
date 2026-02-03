#pragma once

#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {
    
    class Entity : public AnimatedSprite2D {
        GDCLASS(Entity, AnimatedSprite2D)

        private:
            // todo: put member variables here
    
        protected:
            static void _bind_methods();
    
        public:
            Entity();
            ~Entity();
            void _process(double delta) override;
            // todo: put getters and setters here

    };
}