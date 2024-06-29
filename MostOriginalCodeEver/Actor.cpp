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