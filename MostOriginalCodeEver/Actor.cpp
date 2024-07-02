#include "Actor.h"

bool bActorsCollide(Actor actorA, Actor actorB)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = actorA.position.x;
    rightA = leftA + actorA.image->w;
    topA = actorA.position.y;
    bottomA = topA + actorA.image->h;

    leftB = actorB.position.x;
    rightB = leftB + actorB.image->w;
    topB = actorB.position.y;
    bottomB = topB + actorB.image->h;

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

bool ActorCanMoveInDirection(Vector2 vector, Actor actor, Actor Walls[21])
{
    if (actor.position.y + vector.y < 0 && actor.position.y + vector.y + actor.image->h > 480) return false;
    if (actor.position.x + vector.x < 0 && actor.position.x + vector.x + actor.image->w < 640) return false;

    actor.position.x += vector.x;
    actor.position.y += vector.y;
    actor.rect.x = actor.position.x;
    actor.rect.y = actor.position.y;

    for (int i = 0; i < 21; i++)
    {
        if (bActorsCollide(actor, Walls[i]))
        {
            return false;
        }
    }

    return true;
}