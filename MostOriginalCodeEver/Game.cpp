#include "Game.h"

void RestartGame()
{
    gameEnded = false;
    SDL_FreeSurface(EndScreen.background);
    SDL_FreeSurface(EndScreen.PointsText.Surface);
    SDL_FreeSurface(EndScreen.HighScoreText.Surface);
    SDL_FreeSurface(EndScreen.GameOverText.Surface);
    SDL_FreeSurface(EndScreen.RestartText.Surface);

    points = 0;
    PointsText.text = "points: " + std::to_string(points);
    UpdateText(PointsText, font);

    Turtle.rect.x = 700 / 2 - (Turtle.image->w / 2);
    Turtle.position.x = Turtle.rect.x;
    Turtle.rect.y = 200 / 2 - (Turtle.image->h / 2);
    Turtle.position.y = Turtle.rect.y;
    Octopuses[0].rect.x = 40;
    Octopuses[0].rect.y = 40;
    Octopuses[0].position.x = 40;
    Octopuses[0].position.y = 40;

    Octopuses.erase(Octopuses.begin() + 1, Octopuses.end());

    ChangePointLocation(Point, Walls);
    UpdateImage(gameEnded,Walls,WallImage, Turtle, Octopuses, Point, EndScreen, screenSurface, bgImage, PointsText, HighScoreText, window);
}

void CalculateDeltaTime()
{
    tickTime = SDL_GetTicks();
    deltaTime = tickTime - lastTickTime;
    lastTickTime = tickTime;
}

void AddEnemy()
{
    if (Octopuses.size() < 12)
    {
        Actor Octopus;
        Octopus.image = SDL_LoadBMP("octopus.bmp");
        SDL_assert(Octopus.image != nullptr);
        Octopus.rect.x = 40;
        Octopus.rect.y = 40;
        Octopus.position.x = 40;
        Octopus.position.y = 40;
        Octopuses.push_back(Octopus);
    }
}

void CollectPoint()
{
    points++;
    PointsText.text = "points: " + std::to_string(points);
    UpdateText(PointsText, font);
    if (points > highScore)
    {
        highScore = points;
        HighScoreText.text = "high score: " + std::to_string(highScore);
        UpdateText(HighScoreText, font);
    }
    if (points % 10 == 0)
    {
        AddEnemy();
    }
    ChangePointLocation(Point, Walls);
}

void SaveHighScore()
{
    std::ofstream HighScoreFile("hs.txt");
    HighScoreFile << highScore;
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

    WallImage = SDL_LoadBMP("wall.bmp");

    font = TTF_OpenFont("Font.ttf", 40);
    SDL_assert(font != nullptr);

    PointsText.text = "points: " + std::to_string(points);
    PointsText.Surface = TTF_RenderText_Solid(font, PointsText.text.c_str(), SDL_Color{ 255,255,255 });

    std::ifstream HighScoreFile("hs.txt");
    HighScoreFile >> highScore;
    HighScoreFile.close();
    remove("hs.txt");
    HighScoreText.text = "high score: " + std::to_string(highScore);
    HighScoreText.Surface = TTF_RenderText_Solid(font, HighScoreText.text.c_str(), SDL_Color{ 255,255,255 });
    HighScoreText.rect.x = SCREEN_WIDTH - 40 - HighScoreText.Surface->w;

    Turtle.image = SDL_LoadBMP("Turtle.bmp");
    SDL_assert(Turtle.image != nullptr);
    Turtle.walkSound = Mix_LoadWAV("turtleWalkSound.wav");
    SDL_assert(Turtle.walkSound != nullptr);
    Turtle.rect.x = 700 / 2 - (Turtle.image->w / 2);
    Turtle.position.x = Turtle.rect.x;
    Turtle.rect.y = 200 / 2 - (Turtle.image->h / 2);
    Turtle.position.y = Turtle.rect.y;

    Actor Octopus;
    Octopus.image = SDL_LoadBMP("octopus.bmp");
    SDL_assert(Octopus.image != nullptr);
    Octopus.rect.x = 40;
    Octopus.rect.y = 40;
    Octopus.position.x = 40;
    Octopus.position.y = 40;
    Octopuses.push_back(Octopus);

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
            SaveHighScore();
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
            for (Actor &Octopus : Octopuses)
            {
                UpdateOctopusPosition(deltaTime, Octopus, Walls);
                if (bActorsCollide(Turtle, Octopus))
                {
                    CreateEndScreen(EndScreen, font, points, highScore);
                    gameEnded = true;
                }
            }
            if (bActorsCollide(Turtle, Point)) CollectPoint();
        }

        UpdateImage(gameEnded,Walls, WallImage, Turtle, Octopuses, Point, EndScreen, screenSurface, bgImage, PointsText, HighScoreText, window);
    }

    SDL_DestroyWindow(window);
    Mix_FreeChunk(Turtle.walkSound);
    Mix_FreeMusic(bgMusic);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}