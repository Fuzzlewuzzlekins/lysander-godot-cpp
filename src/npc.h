#pragma once

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>

namespace godot {
    
    class NPC : public AnimatedSprite2D {
        GDCLASS(NPC, AnimatedSprite2D)

        private:
            double entSpeed;
            double animFrameRate;
            Area2D* hitbox;
            bool interactible;
    
        protected:
            static void _bind_methods();
    
        public:
            NPC();
            ~NPC();
            void _ready() override;
            void _process(double delta) override;
            void _on_animation_finished();
            void set_entity_speed(const double p_entSpeed); 
            double get_entity_speed() const;
            void set_anim_frame_rate(const double p_animFrameRate);
            double get_anim_frame_rate() const;

    };
}