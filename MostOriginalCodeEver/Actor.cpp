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

bool ActorCanMoveInDirection(Vector2 vector, Actor actor, int Walls[12][16])
{
    if (actor.position.y + vector.y < 0 && actor.position.y + vector.y + actor.image->h > 480) return false;
    if (actor.position.x + vector.x < 0 && actor.position.x + vector.x + actor.image->w < 640) return false;

    actor.position.x += vector.x;
    actor.position.y += vector.y;
    actor.rect.x = actor.position.x;
    actor.rect.y = actor.position.y;

    int ActorYSquareBottom = std::floor((actor.position.y + actor.image->h - 1) / 40.0);
    int ActorYSquareTop = std::floor(actor.position.y / 40.0);
    int ActorXSquareRight = std::floor((actor.position.x + actor.image->w - 1) / 40.0);
    int ActorXSquareLeft = std::floor(actor.position.x / 40.0 - 0.01);

    if (vector.x > 0)
    {
        if (Walls[ActorYSquareTop][ActorXSquareRight] == 1) return false;
        if (Walls[ActorYSquareBottom][ActorXSquareRight] == 1) return false;
        return true;
    }
    if (vector.y > 0)
    {
        if ( Walls[ActorYSquareBottom][ActorXSquareLeft] == 1) return false;
        if (Walls[ActorYSquareBottom][ActorXSquareRight] == 1) return false;
        return true;
    }
    if (Walls[ActorYSquareTop][ActorXSquareLeft] == 1) return false;
    return true;
}