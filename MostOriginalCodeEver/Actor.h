#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Vector.h"

struct Actor
{
    SDL_Surface* image;
    Vector2 position;
    Vector2 direction = Vector2{ 0,0.1 };
    SDL_Rect rect;
    Mix_Chunk* walkSound;
};

bool bActorsCollide(Actor actorA, Actor actorB);
bool ActorCanMoveInDirection(Vector2 vector, Actor actor, int Walls[12][16]);