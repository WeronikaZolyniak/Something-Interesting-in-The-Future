#include "Physics.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

void UpdateActorPosition(Actor& actor, Vector2 vector, Actor Walls[20])
{
    Vector2 v = { 0,0 };
    if (actor.position.y + vector.y > 0 && actor.position.y + vector.y + actor.image->h < SCREEN_HEIGHT) v.y = vector.y;
    if (actor.position.x + vector.x > 0 && actor.position.x + vector.x + actor.image->w < SCREEN_WIDTH) v.x = vector.x;

    actor.position += v;
    actor.rect.x = actor.position.x;
    actor.rect.y = actor.position.y;

    for (int i = 0; i < 21; i++)
    {
        if (bActorsCollide(actor, Walls[i]))
        {
            actor.position -= v;
            actor.rect.x = actor.position.x;
            actor.rect.y = actor.position.y;
            return;
        }
    }
    
    
    
}

void UpdateActorMovement(Actor& actor, Vector2 vector, Actor Walls[20])
{
    if (vector.x == 0 && vector.y == 0) return;
    UpdateActorPosition(actor, vector, Walls);
    PlayActorSound(actor);
}

void ChangePointLocation(Actor &Point, Actor Walls[20])
{
    float newx = rand() % (SCREEN_WIDTH - Point.image->w);
    float newy = rand() % (SCREEN_HEIGHT - Point.image->h);
    Vector2 v = { newx, newy };

    Point.position = Vector2{ 0,0 };
    UpdateActorMovement(Point, v, Walls);
}

void UpdateOctopusPosition(uint32_t deltaTime, Actor &Octopus, Actor &Turtle, Actor Walls[20])
{
    Vector2 v = { 0,0 };

    if (Octopus.position.x < Turtle.position.x) v += Vector2{ 0.1,0 };
    else if (Octopus.position.x > Turtle.position.x) v += Vector2{ -0.1,0 };

    if (Octopus.position.y < Turtle.position.y) v += Vector2{ 0,0.1 };
    else if (Octopus.position.y > Turtle.position.y) v += Vector2{ 0,-0.1 };

    UpdateActorMovement(Octopus, v * deltaTime, Walls);
}

void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, Actor Walls[20])
{
    InputVector.Normalize();
    UpdateActorMovement(Turtle, InputVector * 0.3 * deltaTime, Walls);
    //std::cout << "x: " << Turtle.rect.x << "y: " << Turtle.rect.y << std::endl;
    InputVector = Vector2{ 0,0 };
}