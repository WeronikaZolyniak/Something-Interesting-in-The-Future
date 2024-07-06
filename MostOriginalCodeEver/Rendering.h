#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Actor.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Overlay
{
    SDL_Surface* background;
    const char* text;
    SDL_Surface* textSurface;
    const char* RestartText = "Press space to play again";
    SDL_Surface* RestartTextSurface;
};


void UpdateImage(bool gameEnded, int Walls[12][16], SDL_Surface* WallImage, Actor Turtle, Actor Octopus, Actor Point, Overlay EndScreen,
    SDL_Surface* screenSurface, SDL_Surface* bgImage, SDL_Surface* pointsSurface, SDL_Window* window);
void CreateWinScreen(Overlay &EndScreen, TTF_Font* font);
void CreateLoseScreen(Overlay &EndScreen, TTF_Font* font);
void ActivateOverlay(Overlay overlay, SDL_Surface* &screenSurface);
void UpdatePointsText(int points, SDL_Surface*& pointsSurface, TTF_Font* font);
