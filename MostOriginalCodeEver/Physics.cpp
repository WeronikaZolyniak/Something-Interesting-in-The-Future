#include "Physics.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

bool UpdateActorPosition(Actor& actor, Vector2 vector, int Walls[12][16])
{
    Vector2 v = { 0,0 };
    if (actor.position.y + vector.y > 0 && actor.position.y + vector.y + actor.image->h < SCREEN_HEIGHT) v.y = vector.y;
    if (actor.position.x + vector.x > 0 && actor.position.x + vector.x + actor.image->w < SCREEN_WIDTH) v.x = vector.x;

    if (ActorCanMoveInDirection(vector, actor, Walls))
    {
        actor.position += v;
        actor.rect.x = actor.position.x;
        actor.rect.y = actor.position.y;
        return true;
    }
    else return false; 
}

bool UpdateActorMovement(Actor& actor, Vector2 vector, int Walls[12][16])
{
    if (vector.x == 0 && vector.y == 0) return false;
    PlayActorSound(actor);
    return UpdateActorPosition(actor, vector, Walls);
}

void ChangePointLocation(Actor &Point, int Walls[12][16])
{

    float newx = rand() % (SCREEN_WIDTH - Point.image->w);
    float newy = rand() % (SCREEN_HEIGHT - Point.image->h);
    Vector2 v = { newx, newy };
    Point.position = Vector2{ 0,0 };

    if (!ActorCanMoveInDirection(v, Point, Walls)) ChangePointLocation(Point, Walls);
    else
    {
        UpdateActorPosition(Point, v, Walls);
        return;
    } 
}

void UpdateOctopusPosition(uint32_t deltaTime, Actor &Octopus, int Walls[12][16])
{
    std::vector<Vector2> directions;

    Vector2 m_octopusDirection = { -Octopus.direction.x, -Octopus.direction.y };

    if (ActorCanMoveInDirection(Vector2{ 0.1,0 }, Octopus, Walls) && Vector2 { 0.1, 0 } != m_octopusDirection)
    {
        directions.push_back(Vector2{ 0.1,0 });
    }
    if (ActorCanMoveInDirection(Vector2{ 0,0.1 }, Octopus, Walls) && Vector2 { 0, 0.1 } != m_octopusDirection)
    {
        directions.push_back(Vector2{ 0,0.1 });
    }
    if (ActorCanMoveInDirection(Vector2{ -0.1,0 }, Octopus, Walls) && Vector2 { -0.1, -0 } != m_octopusDirection)
    {
        directions.push_back(Vector2{ -0.1,0 });
    }
    if (ActorCanMoveInDirection(Vector2{ 0,-0.1 }, Octopus, Walls) && Vector2 { -0, -0.1 } != m_octopusDirection)
    {
        directions.push_back(Vector2{ 0,-0.1 });
    }

    if (ActorCanMoveInDirection(Octopus.direction, Octopus, Walls) || directions.size() == 0)
    {
        Vector2 FinalDirection = Octopus.direction * deltaTime;

        UpdateActorPosition(Octopus, FinalDirection, Walls);
        return;
    }
    else
    {
        int NewDirectionIndex = rand() % directions.size();

        Vector2 FinalDirection = directions[NewDirectionIndex] * deltaTime;

        UpdateActorPosition(Octopus, FinalDirection, Walls);
        Octopus.direction = directions[NewDirectionIndex];
    }
}

void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, int Walls[12][16])
{
    InputVector.Normalize();
    UpdateActorMovement(Turtle, InputVector * 0.15 * deltaTime, Walls);
    InputVector = Vector2{ 0,0 };
}