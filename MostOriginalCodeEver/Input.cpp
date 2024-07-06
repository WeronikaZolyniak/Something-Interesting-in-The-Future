#include "Input.h"

SDL_Event GetInputEvent()
{
	SDL_Event event;
    while (SDL_PollEvent(&event))
    {
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
        return InputVector;
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        InputVector += Vector2{ -1,0 };
        return InputVector;
    }
    if (state[SDL_SCANCODE_UP])
    {
        InputVector += Vector2{ 0,-1 };
        return InputVector;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        InputVector += Vector2{ 0,1 };
        return InputVector;
    }
    return InputVector;
}