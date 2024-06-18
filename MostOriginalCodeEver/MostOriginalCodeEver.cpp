﻿#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <utility>
#include <iostream>
#include <string>
#include "MostOriginalHeader.h"

void Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) exit(-1);
    if (TTF_Init() == -1) exit(-1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) exit(-1);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (window == nullptr) exit(-1);

    bgImage = SDL_LoadBMP("image.bmp");
    SDL_assert(bgImage != nullptr);

    Turtle.image = SDL_LoadBMP("Turtle.bmp");
    SDL_assert(Turtle.image != nullptr);
    Turtle.walkSound = Mix_LoadWAV("turtleWalkSound.wav");
    SDL_assert(Turtle.walkSound != nullptr);
    Turtle.rect.x = SCREEN_WIDTH / 2 - (Turtle.image->w / 2);
    Turtle.position.x = Turtle.rect.x;
    Turtle.rect.y = SCREEN_HEIGHT / 2 - (Turtle.image->h / 2);
    Turtle.position.y = Turtle.rect.y;

    Octopus.image = SDL_LoadBMP("octopus.bmp"); 
    SDL_assert(Octopus.image != nullptr);

    Point.image = SDL_LoadBMP("Seashell.bmp");
    SDL_assert(Point.image != nullptr);
    ChangePointLocation();

    bgMusic = Mix_LoadMUS("backgroundMusic.wav");
    SDL_assert(bgMusic != nullptr);

    font = TTF_OpenFont("Font.ttf", 40);
    SDL_assert(font != nullptr);

    std::string str_points = std::to_string(points);
    pointsSurface = TTF_RenderText_Solid(font, str_points.c_str(), SDL_Color{ 166,126,163 });
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
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
            {
                if (Mix_Playing(1) != 0) Mix_HaltChannel(1);
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_SPACE && gameEnded) RestartGame();
        }
    }

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
}

void UpdateImage()
{
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(bgImage, NULL, screenSurface, NULL);
    SDL_BlitSurface(Turtle.image, NULL, screenSurface, &Turtle.rect);
    SDL_BlitSurface(Octopus.image, NULL, screenSurface, &Octopus.rect);
    SDL_BlitSurface(Point.image, NULL, screenSurface, &Point.rect);
    SDL_BlitSurface(pointsSurface, NULL, screenSurface, NULL);
    if (gameEnded) ActivateOverlay(EndScreen);
    SDL_UpdateWindowSurface(window);
}

void RestartGame()
{
    gameEnded = false;
    std::cout << gameEnded << std::endl;
    SDL_FreeSurface(EndScreen.background);
    EndScreen.text = "";
    SDL_FreeSurface(EndScreen.textSurface);
    SDL_FreeSurface(EndScreen.RestartTextSurface);

    points = 0;
    std::string str_points = std::to_string(points);
    SDL_FreeSurface(pointsSurface);
    pointsSurface = TTF_RenderText_Solid(font, str_points.c_str(), SDL_Color{ 166,126,163 });

    Turtle.rect.x = SCREEN_WIDTH / 2 - (Turtle.image->w / 2);
    Turtle.position.x = Turtle.rect.x;
    Turtle.rect.y = SCREEN_HEIGHT / 2 - (Turtle.image->h / 2);
    Turtle.position.y = Turtle.rect.y;
    Octopus.rect.x = 0;
    Octopus.rect.y = 0;
    Octopus.position.x = Octopus.rect.x;
    Octopus.position.y = Octopus.rect.y;

    ChangePointLocation();
    UpdateImage();
}

bool bActorsCollide(Actor actorA, Actor actorB)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = actorA.rect.x;
    rightA = leftA + actorA.rect.w;
    topA = actorA.rect.y;
    bottomA = topA + actorA.rect.h;

    leftB = actorB.rect.x;
    rightB = leftB + actorB.rect.w;
    topB = actorB.rect.y;
    bottomB = topB + actorB.rect.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

void CreateWinScreen()
{
    EndScreen.background = SDL_LoadBMP("overlayBackground.bmp");
    SDL_assert(EndScreen.background != nullptr);
    EndScreen.text = "Congratulations, you won!";
    EndScreen.textSurface = TTF_RenderText_Solid(font, EndScreen.text, SDL_Color{ 166,126,163 });
    EndScreen.RestartTextSurface = TTF_RenderText_Solid(font, EndScreen.RestartText, SDL_Color{ 255,255,255 });
}

void CreateLoseScreen()
{
    EndScreen.background = SDL_LoadBMP("overlayBackground.bmp");
    SDL_assert(EndScreen.background != nullptr);
    EndScreen.text = "You lost";
    EndScreen.textSurface = TTF_RenderText_Solid(font, EndScreen.text, SDL_Color{ 166,126,163 });
    EndScreen.RestartTextSurface = TTF_RenderText_Solid(font, EndScreen.RestartText, SDL_Color{ 255,255,255 });
}

void ActivateOverlay(Overlay overlay)
{
    SDL_BlitSurface(overlay.background, NULL, screenSurface, NULL);
    SDL_Rect TextRect;
    TextRect.y = SCREEN_HEIGHT / 2 - overlay.textSurface->h /2;
    TextRect.x = SCREEN_WIDTH / 2 - overlay.textSurface->w / 2;
    SDL_BlitSurface(overlay.textSurface, NULL, screenSurface, &TextRect);
    SDL_Rect RestartTextRect;
    RestartTextRect.y = (4 * SCREEN_HEIGHT) / 5 - overlay.RestartTextSurface->h / 2;
    RestartTextRect.x = SCREEN_WIDTH / 2 - overlay.RestartTextSurface->w / 2;
    SDL_BlitSurface(overlay.RestartTextSurface, NULL, screenSurface, &RestartTextRect);
}

void CheckWinCondition()
{
    if (points == 20)
    {
        CreateWinScreen();
        gameEnded = true;
    }
}

void UpdateActorPosition(Actor &actor, Vector2 vector)
{
    if (actor.position.y + vector.y < 0 || actor.position.y + vector.y + actor.image->h > SCREEN_HEIGHT)
    {
         if (vector.x == 0 || actor.position.x + vector.x < 0 || actor.position.x + vector.x + actor.image->w > SCREEN_WIDTH) return;
         else
         {
             actor.position.x += vector.x;
             actor.rect.x = actor.position.x;
             actor.rect.y = actor.position.y;
             return;
         }
    }
    if (actor.position.x + vector.x < 0 || actor.position.x + vector.x + actor.image->w > SCREEN_WIDTH)
    {
        if (vector.y == 0 || actor.position.y + vector.y < 0 || actor.position.y + vector.y + actor.image->h > SCREEN_HEIGHT) return;
        else
        {
            actor.position.y += vector.y;
            actor.rect.x = actor.position.x;
            actor.rect.y = actor.position.y;
            return;
        }
    }

    actor.position += vector;
    actor.rect.x = actor.position.x;
    actor.rect.y = actor.position.y;
}

void UpdateActorMovement(Actor& actor, Vector2 vector)
{
    if (vector.x == 0 && vector.y == 0) return;
    UpdateActorPosition(actor, vector);
    if (Mix_Playing(1) == 0) Mix_PlayChannel(1, actor.walkSound, 0);
}

void ChangePointLocation()
{
    float newx = rand() % (SCREEN_WIDTH - Point.image->w);
    float newy = rand() % (SCREEN_HEIGHT - Point.image->h);
    Vector2 v = { newx, newy };
    
    Point.position = Vector2{ 0,0 };
    UpdateActorMovement(Point, v);
}

void CollectPoint()
{
    points++;
    std::string str_points = std::to_string(points);
    SDL_FreeSurface(pointsSurface);
    pointsSurface = TTF_RenderText_Solid(font, str_points.c_str(), SDL_Color{ 166,126,163 });
    CheckWinCondition();
    ChangePointLocation();
}

void UpdateOctopusPosition()
{
    Vector2 v = { 0,0 };

    if (Octopus.position.x < Turtle.position.x) v += Vector2{ 0.1,0 };
    else if (Octopus.position.x > Turtle.position.x) v += Vector2{ -0.1,0 };

    if (Octopus.position.y < Turtle.position.y) v += Vector2{ 0,0.1 };
    else if (Octopus.position.y > Turtle.position.y) v += Vector2{ 0,-0.1 };

    UpdateActorMovement(Octopus, v * deltaTime);
}

void UpdateTurtlePosition()
{
    InputVector.Normalize();
    UpdateActorMovement(Turtle, InputVector * 0.3 * deltaTime);
    InputVector = Vector2{ 0,0 };
}

void CalculateDeltaTime()
{
    tickTime = SDL_GetTicks();
    deltaTime = tickTime - lastTickTime;
    lastTickTime = tickTime;
}

int main(int argc, char* args[])
{
    Init();
    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(30);

    SDL_Event event;
    while (bGameLoop)
    {
        CalculateDeltaTime();
        InputHandling(event, bGameLoop);
        if (gameEnded && Mix_Playing(1) != 0) Mix_HaltChannel(1);
        if (!gameEnded)
        {
            UpdateTurtlePosition();
            UpdateOctopusPosition();
            if (bActorsCollide(Turtle, Point)) CollectPoint();
            if (bActorsCollide(Turtle, Octopus))
            {
                CreateLoseScreen();
                gameEnded = true;
            }
        }
        
        UpdateImage();
    }

    SDL_DestroyWindow(window);
    Mix_FreeChunk(Turtle.walkSound);
    Mix_FreeMusic(bgMusic);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

