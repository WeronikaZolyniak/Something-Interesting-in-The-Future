#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
using namespace std;

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

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* image = NULL;
SDL_Surface* turtle = NULL;
SDL_Rect turtlePosition;
Vector2 turtleDisplacementVector;
Mix_Chunk* turtleWalkSound;
Mix_Music* bgMusic;

void Init()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) exit(-1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) exit(-1);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    image = SDL_LoadBMP("image.bmp");
    SDL_assert(image != nullptr);
    turtle = SDL_LoadBMP("Turtle.bmp");
    SDL_assert(turtle != nullptr);

    turtleWalkSound = Mix_LoadWAV("turtleWalkSound.wav");
    SDL_assert(turtleWalkSound != nullptr);
    bgMusic = Mix_LoadMUS("backgroundMusic.wav");
    SDL_assert(bgMusic != nullptr);

    if (window == nullptr) exit(-1);
}

void UpdateImage()
{
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(image, NULL, screenSurface, NULL);
    SDL_BlitSurface(turtle, NULL, screenSurface, &turtlePosition);

    SDL_UpdateWindowSurface(window);
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
                            if (turtlePosition.y > 0) turtleDisplacementVector += {0, -4};
                            if (Mix_Playing(1) == 0) Mix_PlayChannel(1, turtleWalkSound, 0);
                            break;
                        case SDLK_DOWN:
                            if (turtlePosition.y + 104 < SDL_GetWindowSurface(window)->h) turtleDisplacementVector += {0, 4};
                            if (Mix_Playing(1) == 0) Mix_PlayChannel(1, turtleWalkSound, 0);
                            break;
                        case SDLK_RIGHT:
                            if (turtlePosition.x + 104 < SDL_GetWindowSurface(window)->w) turtleDisplacementVector += {4, 0};
                            if (Mix_Playing(1) == 0) Mix_PlayChannel(1, turtleWalkSound, 0);
                            break;
                        case SDLK_LEFT:
                            if (turtlePosition.x > 0) turtleDisplacementVector += {-4, 0};
                            if (Mix_Playing(1) == 0) Mix_PlayChannel(1, turtleWalkSound, 0);
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
        turtlePosition.x = turtleDisplacementVector.x;
        turtlePosition.y = turtleDisplacementVector.y;
        UpdateImage();
    }

    SDL_DestroyWindow(window);
    Mix_FreeChunk(turtleWalkSound);
    Mix_FreeMusic(bgMusic);
    Mix_Quit();
    SDL_Quit();
    return 0;
}

