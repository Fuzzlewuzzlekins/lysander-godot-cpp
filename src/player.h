#pragma once

#include "entity.h"

namespace godot {
    
    class Player : public Entity {
        GDCLASS(Player, Entity)
    
        private:
            Area2D* closestArea;
        
        protected:
            static void _bind_methods();
    
        public:
            Player();
            ~Player();
            void _ready() override;
            void _process(double delta) override;

    };
}