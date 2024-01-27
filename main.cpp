/*
main.cpp
The main game process.
*/

#include <cmath>
#include "raylib.h"
#include "main.h"

int main()
{
    InitWindow(WindowWidth, WindowHeight, "Asteroid Survivor");
    InitialiseGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Game logic begins.
        switch (CurrentGameState)
        {
            case MainMenu:
                DrawMainMenu();
                break;
            case Play:
                DrawPlay();
                break;
            case GameOver:
                DrawGameOver();
                break;
        }
        // Game logic ends.

        EndDrawing();
    }
}

void DrawMainMenu()
{
    DrawText("Asteroid Survivor", MidpointCoordinate[0], MidpointCoordinate[1], 80, WHITE);
    DrawText("Press SPACE to begin.", SubtitleCoordinate[0], SubtitleCoordinate[1], 40, WHITE);
    if (IsKeyDown(KEY_SPACE))
    {
        CurrentGameState = GameState::Play;
    }
}

void DrawPlay()
{
    SpawnAsteroidAtInterval();
    UpdateAllActors();
    UpdateScore();
    UpdateUI();
}

void DrawGameOver()
{
    string scoreString = "Your score: ." + to_string(Score);
    const char* scoreLabel = scoreString.c_str();

    DrawText("GAME OVER", MidpointCoordinate[0], MidpointCoordinate[1], 80, RED);
    DrawText(scoreLabel, SubtitleCoordinate[0], SubtitleCoordinate[1], 40, WHITE);
    DrawText("Press SPACE to quit.", QuitCoordinate[0], QuitCoordinate[1], 40, WHITE);
    if (IsKeyDown(KEY_SPACE))
    {
        exit(0);
    }
}

void InitialiseGame()
{
    SetTargetFPS(60);
    srand(time(NULL));
    
    Vector2 spawnPoint = {(WindowWidth/2), (WindowHeight/2)};
    Player = {spawnPoint};
}

void UpdateAllActors()
{
    Player.Update();

    std::list<AAsteroid>::iterator iterator = Asteroids.begin();
    int numberOfAsteroids = Asteroids.size();
    for (int index = 0; index < numberOfAsteroids; ++index)
    {
        AAsteroid& currentAsteroid = *iterator;
        currentAsteroid.Update();
        advance(iterator, 1);
    }

    iterator = Asteroids.begin();
    for (int index = 0; index < numberOfAsteroids; ++index)
    {
        AAsteroid& currentAsteroid = *iterator;

        vector<vector<int>> asteroidVerts = currentAsteroid.GetRectVerts();
        bool isCollidingWithPlayer = Player.CollisionCheck(asteroidVerts);
        if (isCollidingWithPlayer)
        {
            Asteroids.remove(currentAsteroid);
            CurrentGameState = GameState::GameOver;
            break;
        }

        advance(iterator, 1);
    }
}

void UpdateScore()
{
    Score += 1;
}

void UpdateUI()
{
    std::string scoreString = std::to_string(Score);
    char const *scoreText = scoreString.c_str();
    DrawText(scoreText, Player.Position.x, Player.Position.y, 40, YELLOW);
}


void SpawnAsteroidAtInterval()
{
    if (AsteroidSpawnTimer >= AsteroidSpawnRate)
    {
        AsteroidSpawnTimer = 0.0f;

        // Create new Asteroid.
        Vector2 spawnPos = GetRandomSpawnPosition();
        Vector2 velocity = GetNormalisedVectorToPlayer(spawnPos);
        AAsteroid newAsteroid = {spawnPos, velocity};
        Asteroids.push_back(newAsteroid);

        // Despawn oldest Asteroid.
        if ((int)Asteroids.size() > (int)MaxAsteroidsSpawned)
        {
            Asteroids.remove(Asteroids.front());
        }
    }
    else
    {
        AsteroidSpawnTimer += GetFrameTime();
    }
}

Vector2 GetRandomSpawnPosition()
{
    Vector2 spawnPosition {};
    int sideToSpawnAt = GetRandomValue(0, sizeof(SpawnSides));

    switch (sideToSpawnAt)
    {
        case 0: // Top
            spawnPosition.x = GetRandomValue(0, WindowWidth);
            spawnPosition.y = 0;
            break;
        case 1: // Right
            spawnPosition.x = WindowWidth;
            spawnPosition.y = GetRandomValue(0, WindowHeight);
            break;
        case 2: // Bottom
            spawnPosition.x = GetRandomValue(0, WindowWidth);
            spawnPosition.y = WindowHeight;
            break;
        case 3: // Left
            spawnPosition.x = 0;
            spawnPosition.y = GetRandomValue(0, WindowHeight);
            break;
    }

    return spawnPosition;
}

Vector2 GetNormalisedVectorToPlayer(Vector2 objectPosition)
{
    Vector2 movementVector = {(Player.Position.x - objectPosition.x), (Player.Position.y - objectPosition.y)};
    float magnitude = sqrt((movementVector.x*movementVector.x) + (movementVector.y*movementVector.y));
    Vector2 normalisedVector = {(movementVector.x / magnitude), (movementVector.y / magnitude)};
    return normalisedVector;
}