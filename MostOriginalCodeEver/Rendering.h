#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Actor.h"
#include <string>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Text
{
    std::string text;
    SDL_Surface* Surface;
    SDL_Rect rect;
};

struct Overlay
{
    SDL_Surface* background;
    Text PointsText;
    Text HighScoreText;
    Text GameOverText;
    Text RestartText;
};

void UpdateImage(bool gameEnded, int Walls[12][16], SDL_Surface* WallImage, Actor Turtle, std::vector<Actor> Octopuses, Actor Point, Overlay EndScreen,
    SDL_Surface* screenSurface, SDL_Surface* bgImage, Text PointsText, Text HighScoreText, SDL_Window* window);
void CreateEndScreen(Overlay &EndScreen, TTF_Font* font, int points, int highScore);
void ActivateOverlay(Overlay overlay, SDL_Surface* &screenSurface);
void UpdateText(Text &text, TTF_Font* font);
