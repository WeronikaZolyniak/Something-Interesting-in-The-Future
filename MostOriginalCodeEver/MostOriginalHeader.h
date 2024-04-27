#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Vector2
{
    float x;
    float y;

    void operator+=(Vector2 v)
    {
        x += v.x;
        y += v.y;
    }
};

struct Actor
{
    SDL_Surface* image;
    SDL_Rect position;
};

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* image = NULL;
int octopusDirection = 1;
Mix_Chunk* turtleWalkSound;
Mix_Music* bgMusic;

Actor Turtle;
Actor Octopus;