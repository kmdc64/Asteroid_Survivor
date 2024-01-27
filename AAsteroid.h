#pragma once

#include <cmath>
#include <bits/stdc++.h>
#include "raylib.h"
#include "Actor.h"

class AAsteroid : public virtual Actor
{
    public:
        float MovementSpeed {10.0};
        int Radius {15};

        AAsteroid(Vector2 position, Vector2 velocity);
        void Update() override;
        void Move() override;
        void Draw() override;
};