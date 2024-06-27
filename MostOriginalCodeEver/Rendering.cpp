#include "Rendering.h"

void UpdateImage(bool gameEnded, Actor Turtle, Actor Octopus, Actor Point, Overlay EndScreen,
    SDL_Surface* screenSurface, SDL_Surface* bgImage, SDL_Surface* pointsSurface, SDL_Window* window)
{
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(bgImage, NULL, screenSurface, NULL);
    SDL_BlitSurface(Turtle.image, NULL, screenSurface, &Turtle.rect);
    SDL_BlitSurface(Octopus.image, NULL, screenSurface, &Octopus.rect);
    SDL_BlitSurface(Point.image, NULL, screenSurface, &Point.rect);
    SDL_BlitSurface(pointsSurface, NULL, screenSurface, NULL);
    if (gameEnded) ActivateOverlay(EndScreen, screenSurface);
    SDL_UpdateWindowSurface(window);
}

void CreateWinScreen(Overlay &EndScreen, TTF_Font* font)
{
    EndScreen.background = SDL_LoadBMP("overlayBackground.bmp");
    SDL_assert(EndScreen.background != nullptr);
    EndScreen.text = "Congratulations, you won!";
    EndScreen.textSurface = TTF_RenderText_Solid(font, EndScreen.text, SDL_Color{ 166,126,163 });
    EndScreen.RestartTextSurface = TTF_RenderText_Solid(font, EndScreen.RestartText, SDL_Color{ 255,255,255 });
}

void CreateLoseScreen(Overlay &EndScreen, TTF_Font* font)
{
    EndScreen.background = SDL_LoadBMP("overlayBackground.bmp");
    SDL_assert(EndScreen.background != nullptr);
    EndScreen.text = "You lost";
    EndScreen.textSurface = TTF_RenderText_Solid(font, EndScreen.text, SDL_Color{ 166,126,163 });
    EndScreen.RestartTextSurface = TTF_RenderText_Solid(font, EndScreen.RestartText, SDL_Color{ 255,255,255 });
}

void ActivateOverlay(Overlay overlay, SDL_Surface* &screenSurface)
{
    SDL_BlitSurface(overlay.background, NULL, screenSurface, NULL);
    SDL_Rect TextRect;
    TextRect.y = 640 / 2 - overlay.textSurface->h / 2;
    TextRect.x = 480 / 2 - overlay.textSurface->w / 2;
    SDL_BlitSurface(overlay.textSurface, NULL, screenSurface, &TextRect);
    SDL_Rect RestartTextRect;
    RestartTextRect.y = (4 * SCREEN_HEIGHT) / 5 - overlay.RestartTextSurface->h / 2;
    RestartTextRect.x = SCREEN_WIDTH / 2 - overlay.RestartTextSurface->w / 2;
    SDL_BlitSurface(overlay.RestartTextSurface, NULL, screenSurface, &RestartTextRect);
}

void UpdatePointsText(int points, SDL_Surface* &pointsSurface, TTF_Font* font)
{
    SDL_FreeSurface(pointsSurface);
    std::string str_points = std::to_string(points);
    pointsSurface = TTF_RenderText_Solid(font, str_points.c_str(), SDL_Color{ 166,126,163 });
}