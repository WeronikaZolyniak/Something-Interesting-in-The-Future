#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
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

Vector2 InputVector = { 0,0 };

Overlay EndScreen;

Actor Turtle;
Actor Octopus;
Actor Point;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bgImage = NULL;
SDL_Surface* pointsSurface = NULL;

TTF_Font* font;

Mix_Music* bgMusic;

void RestartGame();
void CheckWinCondition();
void CalculateDeltaTime();
void QuitGame();