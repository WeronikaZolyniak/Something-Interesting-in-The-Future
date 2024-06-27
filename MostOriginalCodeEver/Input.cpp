#include "Input.h"

SDL_Event GetInputEvent()
{
	SDL_Event event;
    while (SDL_PollEvent(&event))
    {
       /* if (event.type == SDL_QUIT)
        {
            QuitGame();
        }
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
            {
                StopSound(1);
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_SPACE && gameEnded) RestartGame();
        }*/
        return event;
    }
}

Vector2 GetInputVector()
{
    Vector2 InputVector = { 0,0 };
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RIGHT])
    {
        InputVector += Vector2{ 1,0 };
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        InputVector += Vector2{ -1,0 };
    }
    if (state[SDL_SCANCODE_UP])
    {
        InputVector += Vector2{ 0,-1 };
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        InputVector += Vector2{ 0,1 };
    }
    return InputVector;
}