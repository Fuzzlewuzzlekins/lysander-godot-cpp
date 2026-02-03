#pragma once

#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {
    
    class Entity : public AnimatedSprite2D {
        GDCLASS(Entity, AnimatedSprite2D)

        private:
            double entSpeed;
            double animFrameRate;
    
        protected:
            static void _bind_methods();
    
        public:
            Entity();
            ~Entity();
            void _ready() override;
            void _process(double delta) override;
            void set_entity_speed(const double p_entSpeed); 
            double get_entity_speed() const;
            void set_anim_frame_rate(const double p_animFrameRate);
            double get_anim_frame_rate() const;

    };
}