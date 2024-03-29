﻿#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* image = NULL;
    SDL_Surface* turtle = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) return -1;

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    screenSurface = SDL_GetWindowSurface(window);
    image = SDL_LoadBMP("image.bmp");
    turtle = SDL_LoadBMP("Turtle.bmp");

    if (window == nullptr) return -1;
    SDL_Event event;
    bool bGameLoop = true;
    while (bGameLoop)
    {
        while (SDL_PollEvent(&event))
        {
                if (event.type == SDL_QUIT)
                {
                    bGameLoop = false;
                    break;
                }
        }
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        if(image != nullptr) SDL_BlitSurface(image, NULL, screenSurface, NULL);
        if (turtle != nullptr) SDL_BlitSurface(turtle, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

