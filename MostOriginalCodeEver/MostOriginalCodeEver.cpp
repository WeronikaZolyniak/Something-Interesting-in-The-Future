﻿#include <SDL.h>
#include <SDL_mixer.h>
#include <utility>
#include <iostream>
#include "MostOriginalHeader.h"
using namespace std;

/*inline SDL_Rect operator+(SDL_Rect pos, Vector2 v)
{
    
    pos.x += v.x;
    pos.y += v.y;
    return pos;
}*/

void Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) exit(-1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) exit(-1);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (window == nullptr) exit(-1);

    image = SDL_LoadBMP("image.bmp");
    SDL_assert(image != nullptr);

    Turtle.image = SDL_LoadBMP("Turtle.bmp");
    SDL_assert(Turtle.image != nullptr);
    Turtle.walkSound = Mix_LoadWAV("turtleWalkSound.wav");
    SDL_assert(Turtle.walkSound != nullptr);

    Octopus.image = SDL_LoadBMP("octopus.bmp"); 
    SDL_assert(Octopus.image != nullptr);

    bgMusic = Mix_LoadMUS("backgroundMusic.wav");
    SDL_assert(bgMusic != nullptr);
}

void InputHandling(SDL_Event &event, bool &bGameLoop)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            bGameLoop = false;
            break;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                UpdateActorPosition(Turtle, Vector2{ 0,-4 });
                break;
            case SDLK_DOWN:
                UpdateActorPosition(Turtle, Vector2{ 0,4 });
                break;
            case SDLK_RIGHT:
                UpdateActorPosition(Turtle, Vector2{ 4,0 });
                break;
            case SDLK_LEFT:
                UpdateActorPosition(Turtle, Vector2{ -4,0 });
                break;
            }
        }
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
            {
                if (Mix_Playing(1) != 0) Mix_HaltChannel(1);
            }
        }
    }
}

void UpdateImage()
{
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(image, NULL, screenSurface, NULL);
    SDL_BlitSurface(Turtle.image, NULL, screenSurface, &Turtle.rect);
    SDL_BlitSurface(Octopus.image, NULL, screenSurface, &Octopus.rect);

    SDL_UpdateWindowSurface(window);
}

void UpdateActorPosition(Actor &actor, Vector2 vector)
{
    if (actor.position.y + vector.y < 0 || actor.position.y + vector.y + 100 > SCREEN_HEIGHT) return;
    if (actor.position.x + vector.x < 0 || actor.position.x + vector.x + 100 > SCREEN_WIDTH) return;

    actor.position += vector;
    actor.rect.x = actor.position.x;
    actor.rect.y = actor.position.y;

    if (Mix_Playing(1) == 0) Mix_PlayChannel(1, actor.walkSound, 0);
}

void UpdateOctopusPosition()
{
    if (Octopus.position.x + 104 >= SDL_GetWindowSurface(window)->w) octopusDirection = -1;
    else if (Octopus.position.x <= 10) octopusDirection = 1;
    float x =  0.05 *  octopusDirection;
    UpdateActorPosition(Octopus, Vector2{ x,0 });
    //Octopus.position = Octopus.position + Vector2{x,0};
}

int main(int argc, char* args[])
{
    Init();

    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(30);

    SDL_Event event;
    bool bGameLoop = true;
    while (bGameLoop)
    {
        InputHandling(event, bGameLoop);
        UpdateOctopusPosition();
        UpdateImage();  
    }

    SDL_DestroyWindow(window);
    Mix_FreeChunk(Turtle.walkSound);
    Mix_FreeMusic(bgMusic);
    Mix_Quit();
    SDL_Quit();
    return 0;
}

