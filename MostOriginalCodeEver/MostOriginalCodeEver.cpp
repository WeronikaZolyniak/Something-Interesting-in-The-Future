#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* image = NULL;
SDL_Surface* turtle = NULL;
SDL_Rect turtlePosition;

void Init()
{

    if (SDL_Init(SDL_INIT_VIDEO) == -1) exit(-1);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    image = SDL_LoadBMP("image.bmp");
    turtle = SDL_LoadBMP("Turtle.bmp");

    if (window == nullptr) exit(-1);
}

void UpdateImage()
{
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    if (image != nullptr) SDL_BlitSurface(image, NULL, screenSurface, NULL);
    if (turtle != nullptr) SDL_BlitSurface(turtle, NULL, screenSurface, &turtlePosition);

    SDL_UpdateWindowSurface(window);
}

int main(int argc, char* args[])
{
    Init();

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
                            turtlePosition.y -= 4;
                            break;
                        case SDLK_DOWN:
                            if (turtlePosition.y + 104 < SDL_GetWindowSurface(window)->h) turtlePosition.y += 4;
                            break;
                        case SDLK_RIGHT:
                            if (turtlePosition.x + 104 < SDL_GetWindowSurface(window)->w) turtlePosition.x += 4;
                            break;
                        case SDLK_LEFT:
                            turtlePosition.x -= 4;
                            break;
                    }
                }
        }
        
        UpdateImage();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

