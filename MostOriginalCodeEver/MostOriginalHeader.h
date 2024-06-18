#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Vector2
{
    float x;
    float y;

    void Normalize()
    {
        if (x == 0 && y == 0) return;

        float L = sqrt(x * x + y * y);
        x = x / L;
        y = y / L;
    }

    void operator+=(Vector2 v)
    {
        x += v.x;
        y += v.y;
    }

    Vector2& operator*(float value)
    {
        x *= value;
        y *= value;
        return *this;
    }
    
};

Vector2 operator*(Vector2 v1, Vector2 v2)
{
    return Vector2{ v1.x * v2.x, v1.y * v2.y };
}

struct Overlay
{
    SDL_Surface* background;
    const char* text;
    SDL_Surface* textSurface;
    const char* RestartText = "Press space to play again";
    SDL_Surface* RestartTextSurface;
};

Overlay EndScreen;

struct Actor
{
    SDL_Surface* image;
    Vector2 position;
    Vector2 direction = Vector2{1,0};
    SDL_Rect rect;
    Mix_Chunk* walkSound;
};

uint32_t deltaTime;
uint32_t lastTickTime = 0;
uint32_t tickTime = 0;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bgImage = NULL;
SDL_Surface* pointsSurface = NULL;

Mix_Music* bgMusic;

Actor Turtle;
Actor Octopus;
Actor Point;

Vector2 InputVector = { 0,0 };

int points = 0;

TTF_Font* font;

bool bGameLoop = true;
bool gameEnded = false;

void UpdateActorPosition(Actor& actor, Vector2 vector);

void ActivateOverlay(Overlay overlay);
void RestartGame();
void ChangePointLocation();