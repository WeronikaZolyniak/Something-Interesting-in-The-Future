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

Vector2 operator*(Vector2 v1, Vector2 v2)
{
    return Vector2{ v1.x * v2.x, v1.y * v2.y };
}

struct Actor
{
    SDL_Surface* image;
    Vector2 position;
    Vector2 direction = Vector2{1,0};
    SDL_Rect rect;
    Mix_Chunk* walkSound;
};

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bgImage = NULL;
//int octopusDirection = 1;

Mix_Music* bgMusic;

Actor Turtle;
Actor Octopus;

Vector2 InputVector = { 0,0 };

void UpdateActorPosition(Actor& actor, Vector2 vector);