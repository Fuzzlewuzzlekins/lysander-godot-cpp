#pragma once

#include "entity.h"

namespace godot {
    
    class NPC : public Entity {
        GDCLASS(NPC, Entity)

        private:
            bool interactible;
    
        protected:
            static void _bind_methods();
    
        public:
            NPC();
            ~NPC();
            void _ready() override;
            void _process(double delta) override;

    };
}