#include <SDL.h>
#include <iostream>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* image = NULL;
SDL_Surface* turtle = NULL;
SDL_Rect turtlePosition;

struct DisplacementVector 
{
    int x;
    int y;

    void operator+=( vector<int> v)
    {
        x += v[0];
        y += v[1];
    }
} turtleDisplacementVector;

void Init()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) exit(-1);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    image = SDL_LoadBMP("image.bmp");
    SDL_assert(image != nullptr);
    turtle = SDL_LoadBMP("Turtle.bmp");
    SDL_assert(turtle != nullptr);

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
                            if (turtlePosition.y > 0) turtleDisplacementVector += vector<int>{0, -4};
                            break;
                        case SDLK_DOWN:
                            if (turtlePosition.y + 104 < SDL_GetWindowSurface(window)->h) turtleDisplacementVector += vector<int>{0, 4};
                            break;
                        case SDLK_RIGHT:
                            if (turtlePosition.x + 104 < SDL_GetWindowSurface(window)->w) turtleDisplacementVector += vector<int>{4, 0};
                            break;
                        case SDLK_LEFT:
                            if (turtlePosition.x > 0) turtleDisplacementVector += vector<int>{-4, 0};
                            break;
                    }
                }
        }
        turtlePosition.x = turtleDisplacementVector.x;
        turtlePosition.y = turtleDisplacementVector.y;
        UpdateImage();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

