#pragma once

#include <vector>
#include "raylib.h"

using namespace std;

class Actor
{
    public:
        Vector2 Position {};
        Vector2 Size {5, 5};
        Vector2 Movement {};
        float MovementSpeed {5.0};

        bool operator == (const Actor& s) const 
        {
            bool positionEqual = ((Position.x == s.Position.x) && (Position.y == s.Position.y));
            bool sizeEqual = ((Size.x == s.Size.x) && (Size.y == s.Size.y));
            bool movementEqual = ((Movement.x == s.Movement.x) && (Movement.y == s.Movement.y));;
            bool speedEqual = MovementSpeed == s.MovementSpeed;
            return positionEqual && sizeEqual && movementEqual && speedEqual;
        }

        virtual void Update();
        virtual void Draw();
        virtual void Input();
        virtual void Move();
        virtual Rectangle GetRect();
        virtual vector<vector<int>> GetRectVerts();
        virtual bool CollisionCheck(vector<vector<int>> collidingObjectVerts);
};