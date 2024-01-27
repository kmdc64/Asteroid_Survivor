#pragma once

#include "raylib.h"
#include "Actor.h"

class APlayer : public virtual Actor
{
    public:
        APlayer();
        APlayer(Vector2 position);
        int Radius {25};

        void Update() override;
        void Draw() override;
        void Input() override;  
};