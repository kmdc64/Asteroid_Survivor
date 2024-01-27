/*
Actor.cpp
An object that can move in the game world.
*/

#include "raylib.h"
#include "Actor.h"

void Actor::Update()
{
    Input();
    Move();
    Draw();
}

void Actor::Draw()
{
    DrawRectangle(Position.x, Position.y, Size.x, Size.y, WHITE);
}

void Actor::Input() {};

void Actor::Move()
{
    if (Movement.y > 0)
    {
        Position.y -= MovementSpeed;
    }
    else if (Movement.y < 0)
    {
        Position.y += MovementSpeed;
    }
    if (Movement.x > 0)
    {
        Position.x += MovementSpeed;
    }
    else if (Movement.x < 0)
    {
        Position.x -= MovementSpeed;
    }
}

Rectangle Actor::GetRect()
{
    Rectangle rect = {Position.x, Position.y, Size.x, Size.y};
    return rect;
}

vector<vector<int>> Actor::GetRectVerts()
{
    float thisHalfLength = Size.x / 2.0f;
    float thisHalfHeight = Size.y / 2.0f;
    int points[4][2] {};

    // Top-left
    points[0][0] = Position.x - thisHalfLength;
    points[0][1] = Position.y - thisHalfHeight;
    // Top-right
    points[1][0] = Position.x + thisHalfLength;
    points[1][1] = Position.y - thisHalfHeight;
    // Bottom-right
    points[2][0] = Position.x + thisHalfLength;
    points[2][1] = Position.y + thisHalfHeight;
    // Bottom-left
    points[3][0] = Position.x - thisHalfLength;
    points[3][1] = Position.y + thisHalfHeight;

    vector<vector<int>> verts = {
        {points[0][0], points[0][1]}, 
        {points[1][0], points[1][1]}, 
        {points[2][0], points[2][1]}, 
        {points[3][0], points[3][1]}
    };

    return verts;
}

bool Actor::CollisionCheck(vector<vector<int>> collidingObjectVerts)
{
    vector<vector<int>> localVerts = GetRectVerts();
    int numberOfVerts = collidingObjectVerts.size();

    // Foreach point in the colliding object...
    for (int index = 0; index < numberOfVerts; ++index)
    {
        // Check if it is inbetween the x & y co-ordinates of this rect...
        vector<int> vert = collidingObjectVerts[index];
        vector<int> topLeftCoordinate = localVerts[0];
        vector<int> bottomRightCoordinate = localVerts[2];
        bool inXBounds = false;
        bool inYBounds = false;

        // X-bounds check:
        int xCoordinate = vert[0];
        int leftCoordinate = topLeftCoordinate[0];
        int rightCoordinate = bottomRightCoordinate[0];
        if ((xCoordinate >= leftCoordinate) && (xCoordinate <= rightCoordinate))
        {
            inXBounds = true;
        }
        // Y-bounds check:
        int yCoordinate = vert[1];
        int topCoordinate = topLeftCoordinate[1];
        int bottomCoordinate = bottomRightCoordinate[1];
        if ((yCoordinate <= bottomCoordinate) && (yCoordinate >= topCoordinate))
        {
            inYBounds = true;
        }

        if (inXBounds && inYBounds)
        {
            return true;
        }
    }

    return false;
}