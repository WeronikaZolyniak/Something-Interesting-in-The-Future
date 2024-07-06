#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.h"
#include "Input.h"
#include "Actor.h"
#include "Audio.h"
#include "Rendering.h"
#include "Physics.h"


uint32_t deltaTime;
uint32_t lastTickTime = 0;
uint32_t tickTime = 0;

bool bGameLoop = true;
bool gameEnded = false;

int points = 0;
int highScore = 0;

Vector2 InputVector = { 0,0 };

Overlay EndScreen;

Actor Turtle;
Actor Octopus;
Actor Point;

 int Walls[12][16] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
SDL_Surface* WallImage;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bgImage = NULL;
Text PointsText;
Text HighScoreText;

TTF_Font* font;

Mix_Music* bgMusic;

void RestartGame();
void CalculateDeltaTime();
void QuitGame();