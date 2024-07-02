#include "Physics.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

bool UpdateActorPosition(Actor& actor, Vector2 vector, Actor Walls[21])
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
            return false;
        }
    }
    
    return true;
    
}

bool UpdateActorMovement(Actor& actor, Vector2 vector, Actor Walls[21])
{
    if (vector.x == 0 && vector.y == 0) return false;
    PlayActorSound(actor);
    return UpdateActorPosition(actor, vector, Walls);
}

void ChangePointLocation(Actor &Point, Actor Walls[21])
{
    float newx = rand() % (SCREEN_WIDTH - Point.image->w);
    float newy = rand() % (SCREEN_HEIGHT - Point.image->h);
    Vector2 v = { newx, newy };

    Point.position = Vector2{ 0,0 };
    UpdateActorMovement(Point, v, Walls);
}

//nie dziala z deltaTime
void UpdateOctopusPosition(uint32_t deltaTime, Actor &Octopus, Actor &Turtle, Actor Walls[21])
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
    if (ActorCanMoveInDirection(Vector2{ -0.1,0 }, Octopus, Walls) && Vector2 { -0.1, 0 } != m_octopusDirection)
    {
        directions.push_back(Vector2{ -0.1,0 });
    }
    if (ActorCanMoveInDirection(Vector2{ 0,-0.1 }, Octopus, Walls) && Vector2 { 0, -0.1 } != m_octopusDirection)
    {
        directions.push_back(Vector2{ 0,-0.1 });
    }

    if(directions.size() == 1 && ActorCanMoveInDirection(Octopus.direction, Octopus, Walls))
    {
        UpdateActorPosition(Octopus, Octopus.direction, Walls);
        return;
    }
    else
    {
        int NewDirectionIndex = rand() % directions.size();
        UpdateActorPosition(Octopus, directions[NewDirectionIndex] , Walls);
        Octopus.direction = directions[NewDirectionIndex];
    }
}

void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, Actor Walls[21])
{
    InputVector.Normalize();
    UpdateActorMovement(Turtle, InputVector * 0.15 * deltaTime, Walls);
    InputVector = Vector2{ 0,0 };
}