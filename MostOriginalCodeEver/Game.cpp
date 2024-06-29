#include "Game.h"

void RestartGame()
{
    gameEnded = false;
    SDL_FreeSurface(EndScreen.background);
    EndScreen.text = "";
    SDL_FreeSurface(EndScreen.textSurface);
    SDL_FreeSurface(EndScreen.RestartTextSurface);

    points = 0;
    UpdatePointsText(points, pointsSurface, font);

    Turtle.rect.x = 700 / 2 - (Turtle.image->w / 2);
    Turtle.position.x = Turtle.rect.x;
    Turtle.rect.y = 200 / 2 - (Turtle.image->h / 2);
    Turtle.position.y = Turtle.rect.y;
    Octopus.rect.x = 0;
    Octopus.rect.y = 0;
    Octopus.position.x = Octopus.rect.x;
    Octopus.position.y = Octopus.rect.y;

    ChangePointLocation(Point, Wall);
    UpdateImage(gameEnded,Wall, Turtle, Octopus, Point, EndScreen, screenSurface, bgImage, pointsSurface, window);
}

void CheckWinCondition()
{
    if (points == 2)
    {
        CreateWinScreen(EndScreen, font);
        gameEnded = true;
    }
}

void CalculateDeltaTime()
{
    tickTime = SDL_GetTicks();
    deltaTime = tickTime - lastTickTime;
    lastTickTime = tickTime;
}

void CollectPoint()
{
    points++;
    UpdatePointsText(points, pointsSurface, font);
    CheckWinCondition();
    ChangePointLocation(Point, Wall);
}

void QuitGame()
{
    bGameLoop = false;
}

void Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) exit(-1);
    if (TTF_Init() == -1) exit(-1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) exit(-1);

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (window == nullptr) exit(-1);

    bgImage = SDL_LoadBMP("image.bmp");
    SDL_assert(bgImage != nullptr);

    font = TTF_OpenFont("Font.ttf", 40);
    SDL_assert(font != nullptr);

    std::string str_points = std::to_string(points);
    pointsSurface = TTF_RenderText_Solid(font, str_points.c_str(), SDL_Color{ 166,126,163 });

    Turtle.image = SDL_LoadBMP("Turtle.bmp");
    SDL_assert(Turtle.image != nullptr);
    Turtle.walkSound = Mix_LoadWAV("turtleWalkSound.wav");
    SDL_assert(Turtle.walkSound != nullptr);
    Turtle.rect.x = 700 / 2 - (Turtle.image->w / 2);
    Turtle.position.x = Turtle.rect.x;
    Turtle.rect.y = 200 / 2 - (Turtle.image->h / 2);
    Turtle.position.y = Turtle.rect.y;

    Octopus.image = SDL_LoadBMP("octopus.bmp");
    SDL_assert(Octopus.image != nullptr);

    Point.image = SDL_LoadBMP("Seashell.bmp");
    SDL_assert(Point.image != nullptr);

    Wall.image = SDL_LoadBMP("testRectangle.bmp");
    SDL_assert(Wall.image != nullptr);
    Wall.rect.x = SCREEN_WIDTH / 2 - (Wall.image->w / 2);
    Wall.rect.y = SCREEN_HEIGHT / 2 - (Wall.image->h / 2);
    Wall.position.x = Wall.rect.x;
    Wall.position.y = Wall.rect.y;
    Wall.tag = 'W';

    bgMusic = Mix_LoadMUS("backgroundMusic.wav");
    SDL_assert(bgMusic != nullptr);

    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(30);
    ChangePointLocation(Point, Wall);
}

void ReactToInputEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
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
        }

    }
    
}

int main(int argc, char* args[])
{
    Init();
    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(30);

    while (bGameLoop)
    {
        CalculateDeltaTime();
        
        if (gameEnded) StopSound(1);
        ReactToInputEvent();
        if (!gameEnded)
        {
            
            InputVector = GetInputVector();
            UpdateTurtlePosition(deltaTime, InputVector, Turtle, Wall);
            UpdateOctopusPosition(deltaTime, Octopus, Turtle, Wall);
            if (bActorsCollide(Turtle, Point)) CollectPoint();
           if (bActorsCollide(Turtle, Octopus))
            {
               CreateLoseScreen(EndScreen, font);
               gameEnded = true;
            }
        }

        UpdateImage(gameEnded,Wall, Turtle, Octopus, Point, EndScreen, screenSurface, bgImage, pointsSurface, window);
    }

    SDL_DestroyWindow(window);
    Mix_FreeChunk(Turtle.walkSound);
    Mix_FreeMusic(bgMusic);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}