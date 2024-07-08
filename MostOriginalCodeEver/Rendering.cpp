#include "Rendering.h"

void UpdateImage(bool gameEnded, int Walls[12][16], SDL_Surface* WallImage, Actor Turtle, std::vector<Actor> Octopuses, Actor Point, Overlay EndScreen,
    SDL_Surface* screenSurface, SDL_Surface* bgImage, Text PointsText, Text HighScoreText, SDL_Window* window)
{
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(bgImage, NULL, screenSurface, NULL);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (Walls[i][j] == 1)
            {
                SDL_Rect WallRect;
                WallRect.x = j * 40;
                WallRect.y = i * 40;
                SDL_BlitSurface(WallImage, NULL, screenSurface, &WallRect);
            }
        }
    }

    SDL_BlitSurface(Turtle.image, NULL, screenSurface, &Turtle.rect);
    for (Actor Octopus : Octopuses)
    {
        SDL_BlitSurface(Octopus.image, NULL, screenSurface, &Octopus.rect);
    }
    SDL_BlitSurface(Point.image, NULL, screenSurface, &Point.rect);
    SDL_BlitSurface(PointsText.Surface, NULL, screenSurface, &PointsText.rect);
    SDL_BlitSurface(HighScoreText.Surface, NULL, screenSurface, &HighScoreText.rect);
    if (gameEnded) ActivateOverlay(EndScreen, screenSurface);
    SDL_UpdateWindowSurface(window);
}

void CreateEndScreen(Overlay &EndScreen, TTF_Font* font, int points, int highScore)
{
    EndScreen.background = SDL_LoadBMP("overlayBackground.bmp");
    SDL_assert(EndScreen.background != nullptr);

    EndScreen.GameOverText.text = "Game Over";
    EndScreen.GameOverText.Surface = TTF_RenderText_Solid(font, EndScreen.GameOverText.text.c_str(), SDL_Color{166,126,163});
    EndScreen.GameOverText.rect.x = SCREEN_WIDTH / 2 - EndScreen.GameOverText.Surface->w / 2;
    EndScreen.GameOverText.rect.y = 100;

    EndScreen.PointsText.text = "your points: " + std::to_string(points);
    EndScreen.PointsText.Surface = TTF_RenderText_Solid(font, EndScreen.PointsText.text.c_str(), SDL_Color{ 166,126,163 });
    EndScreen.PointsText.rect.x = SCREEN_WIDTH / 2 - EndScreen.PointsText.Surface->w / 2;
    EndScreen.PointsText.rect.y = 200;

    EndScreen.HighScoreText.text = "high score: " + std::to_string(highScore);
    EndScreen.HighScoreText.Surface = TTF_RenderText_Solid(font, EndScreen.HighScoreText.text.c_str(), SDL_Color{ 166,126,163 });
    EndScreen.HighScoreText.rect.x = SCREEN_WIDTH / 2 - EndScreen.HighScoreText.Surface->w / 2;
    EndScreen.HighScoreText.rect.y = 250;

    EndScreen.RestartText.text = "Press space to play again";
    EndScreen.RestartText.Surface = TTF_RenderText_Solid(font, EndScreen.RestartText.text.c_str(), SDL_Color{ 255,255,255 });
    EndScreen.RestartText.rect.x = SCREEN_WIDTH / 2 - EndScreen.RestartText.Surface->w / 2;
    EndScreen.RestartText.rect.y = 400;
}

void ActivateOverlay(Overlay overlay, SDL_Surface* &screenSurface)
{
    SDL_BlitSurface(overlay.background, NULL, screenSurface, NULL);
    SDL_BlitSurface(overlay.PointsText.Surface, NULL, screenSurface, &overlay.PointsText.rect);
    SDL_BlitSurface(overlay.HighScoreText.Surface, NULL, screenSurface, &overlay.HighScoreText.rect);
    SDL_BlitSurface(overlay.GameOverText.Surface, NULL, screenSurface, &overlay.GameOverText.rect);
    SDL_BlitSurface(overlay.RestartText.Surface, NULL, screenSurface, &overlay.RestartText.rect);
}

void UpdateText(Text &text, TTF_Font* font)
{
    SDL_FreeSurface(text.Surface);
    text.Surface = TTF_RenderText_Solid(font, text.text.c_str(), SDL_Color{ 255,255,255 });
}