/*
APlayer.cpp
A Player object that can move in the game world.
*/

#include "raylib.h"
#include "APlayer.h"

APlayer::APlayer()
{
    float diameter = this->Radius * 2.0f;
    this->Size = {diameter, diameter};
}

APlayer::APlayer(Vector2 position)
{
    this->Position = position;
    float diameter = this->Radius * 2.0f;
    this->Size = {diameter, diameter};
}

void APlayer::Update()
{
    Input();
    Move();
    Draw();
}

void APlayer::Draw()
{
    DrawCircle(Position.x, Position.y, Radius, RED);
}

void APlayer::Input()
{
    Movement = {0, 0};
    if (IsKeyDown(KEY_W))
    {
        Movement.y = 1;
    }
    else if (IsKeyDown(KEY_S))
    {
        Movement.y = -1;
    }
    
    if (IsKeyDown(KEY_A))
    {
        Movement.x = -1;
    }
    else if (IsKeyDown(KEY_D))
    {
        Movement.x = 1;
    }
}