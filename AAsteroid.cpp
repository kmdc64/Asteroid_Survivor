/*
AAsteroid.cpp
An asteroid object that moves in the same direction over its lifetime.
*/

#include "raylib.h"
#include "AAsteroid.h"

AAsteroid::AAsteroid(Vector2 position, Vector2 velocity)
{
    this->Position = position;
    float min = 1.0f;
    float max = MovementSpeed;
    float random = (float)(rand()) / (float)(RAND_MAX);
    float diff = max - min;
    float randomisedIncrement = random * diff;
    float randomSpeedValue = min + randomisedIncrement;
    this->Movement = Vector2 {(velocity.x * randomSpeedValue), (velocity.y * randomSpeedValue)};

    float diameter = this->Radius * 2.0f;
    this->Size = {diameter, diameter};
}

void AAsteroid::Update()
{
    Move();
    Draw();
}

void AAsteroid::Move()
{
    Position.y += Movement.y;
    Position.x += Movement.x;
}

void AAsteroid::Draw()
{
    DrawCircle(Position.x, Position.y, Radius, WHITE);
}