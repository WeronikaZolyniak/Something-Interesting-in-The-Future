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
    Octopus.rect.x = 40;
    Octopus.rect.y = 40;
    Octopus.position.x = 40;
    Octopus.position.y = 40;

    ChangePointLocation(Point, Walls);
    UpdateImage(gameEnded,Walls, Turtle, Octopus, Point, EndScreen, screenSurface, bgImage, pointsSurface, window);
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
    ChangePointLocation(Point, Walls);
}

void QuitGame()
{
    bGameLoop = false;
}

void LevelInit()
{
    Walls[0].image = SDL_LoadBMP("wall1.bmp");
    Walls[0].rect.x = 0;
    Walls[0].rect.y = 0;

    Walls[1].image = SDL_LoadBMP("wall1.bmp");
    Walls[1].rect.x = 0;
    Walls[1].rect.y = SCREEN_HEIGHT - 40;

    Walls[2].image = SDL_LoadBMP("wall2.bmp");
    Walls[2].rect.x = 0;
    Walls[2].rect.y = 40;

    Walls[3].image = SDL_LoadBMP("wall2.bmp");
    Walls[3].rect.x = SCREEN_WIDTH - 40;
    Walls[3].rect.y = 40;

    Walls[4].image = SDL_LoadBMP("wall3.bmp");
    Walls[4].rect.x = 80;
    Walls[4].rect.y = 40;

    Walls[5].image = SDL_LoadBMP("wall3.bmp");
    Walls[5].rect.x = 80;
    Walls[5].rect.y = SCREEN_HEIGHT - 120;

    Walls[6].image = SDL_LoadBMP("wall3.bmp");
    Walls[6].rect.x = SCREEN_WIDTH - 120;
    Walls[6].rect.y = 200;

    Walls[7].image = SDL_LoadBMP("wall4.bmp");
    Walls[7].rect.x = 80;
    Walls[7].rect.y = 120;

    Walls[8].image = SDL_LoadBMP("wall4.bmp");
    Walls[8].rect.x = 160;
    Walls[8].rect.y = 40;

    Walls[9].image = SDL_LoadBMP("wall4.bmp");
    Walls[9].rect.x = SCREEN_WIDTH - 200;
    Walls[9].rect.y = 120;

    Walls[10].image = SDL_LoadBMP("wall4.bmp");
    Walls[10].rect.x = SCREEN_WIDTH - 120;
    Walls[10].rect.y = SCREEN_HEIGHT - 200;

    Walls[11].image = SDL_LoadBMP("wall4.bmp");
    Walls[11].rect.x = 240;
    Walls[11].rect.y = SCREEN_HEIGHT - 200;

    Walls[12].image = SDL_LoadBMP("wall5.bmp");
    Walls[12].rect.x = 40;
    Walls[12].rect.y = SCREEN_HEIGHT - 200;

    Walls[13].image = SDL_LoadBMP("wall5.bmp");
    Walls[13].rect.x = 160;
    Walls[13].rect.y = SCREEN_HEIGHT - 200;

    Walls[14].image = SDL_LoadBMP("wall5.bmp");
    Walls[14].rect.x = SCREEN_WIDTH - 160;
    Walls[14].rect.y = 120;

    Walls[15].image = SDL_LoadBMP("wall6.bmp");
    Walls[15].rect.x = 200;
    Walls[15].rect.y = 120;

    Walls[16].image = SDL_LoadBMP("wall6.bmp");
    Walls[16].rect.x = 280;
    Walls[16].rect.y = SCREEN_HEIGHT - 200;

    Walls[17].image = SDL_LoadBMP("wall6.bmp");
    Walls[17].rect.x = 320;
    Walls[17].rect.y = SCREEN_HEIGHT - 120;

    Walls[18].image = SDL_LoadBMP("wall7.bmp");
    Walls[18].rect.x = 160;
    Walls[18].rect.y = 200;

    Walls[19].image = SDL_LoadBMP("wall8.bmp");
    Walls[19].rect.x = 200;
    Walls[19].rect.y = 40;

    Walls[20].image = SDL_LoadBMP("wall4.bmp");
    Walls[20].rect.x = 160;
    Walls[20].rect.y = SCREEN_HEIGHT - 120;

    for (int i = 0; i < 21; i++)
    {
        Walls[i].position.x = Walls[i].rect.x;
        Walls[i].position.y = Walls[i].rect.y;
    }
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

    LevelInit();

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
    Octopus.rect.x = 40;
    Octopus.rect.y = 40;
    Octopus.position.x = 40;
    Octopus.position.y = 40;

    Point.image = SDL_LoadBMP("Seashell.bmp");
    SDL_assert(Point.image != nullptr);

    bgMusic = Mix_LoadMUS("backgroundMusic.wav");
    SDL_assert(bgMusic != nullptr);

    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(30);
    ChangePointLocation(Point, Walls);
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
            UpdateTurtlePosition(deltaTime, InputVector, Turtle, Walls);
            UpdateOctopusPosition(deltaTime, Octopus, Turtle, Walls);
            if (bActorsCollide(Turtle, Point)) CollectPoint();
           if (bActorsCollide(Turtle, Octopus))
            {
               CreateLoseScreen(EndScreen, font);
               gameEnded = true;
            }
        }

        UpdateImage(gameEnded,Walls, Turtle, Octopus, Point, EndScreen, screenSurface, bgImage, pointsSurface, window);
    }

    SDL_DestroyWindow(window);
    Mix_FreeChunk(Turtle.walkSound);
    Mix_FreeMusic(bgMusic);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}