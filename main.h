#pragma once

#include <list>
#include <vector>
#include "APlayer.h"
#include "AAsteroid.h"

using namespace std;

const static int WindowWidth {1280};
const static int WindowHeight {720};
const vector<float> MidpointCoordinate = {((WindowWidth/2) - 380), (WindowHeight/2)};
const vector<float> SubtitleCoordinate = {(MidpointCoordinate[0] - 80), (MidpointCoordinate[1] + 100)};
const vector<float> QuitCoordinate = {(MidpointCoordinate[0] - 80), (MidpointCoordinate[1] + 200)};

enum GameState
{
    MainMenu,
    Play,
    GameOver
};

enum SpawnSides 
{
    Top,
    Right,
    Bottom,
    Left
};

APlayer Player {};
std::list<AAsteroid> Asteroids;

GameState CurrentGameState;
int MaxAsteroidsSpawned {20};
float AsteroidSpawnRate {1.0f};
float AsteroidSpawnTimer {};
int Score {};

void DrawMainMenu();
void DrawPlay();
void DrawGameOver();
void InitialiseGame();
void UpdateAllActors();
void UpdateScore();
void UpdateUI();
void SpawnAsteroidAtInterval();
Vector2 GetRandomSpawnPosition();
Vector2 GetNormalisedVectorToPlayer(Vector2 objectPosition);
