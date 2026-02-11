#pragma once

#include "entity.h"
#include "player.h"
#include "task.h"

namespace godot {
    
    class NPC : public Entity {
        GDCLASS(NPC, Entity)

        private:
            bool interactible;
            Player* targetPlayer;
    
        protected:
            static void _bind_methods();
    
        public:
            NPC();
            ~NPC();
            void _ready() override;
            void _process(double delta) override;
            void _on_player_interact(Area2D* area);
            void _on_player_highlight(Area2D* area);
            void _on_player_unhighlight(Area2D* area);
            void set_target_player(Player* p_player);
            Player* get_target_player() const;

    };
}