#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Vector.h"

struct Actor
{
    SDL_Surface* image;
    Vector2 position;
    Vector2 direction = Vector2{ 1,0 };
    SDL_Rect rect;
    Mix_Chunk* walkSound;
};

bool bActorsCollide(Actor actorA, Actor actorB);