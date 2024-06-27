#include "Actor.h"

bool bActorsCollide(Actor actorA, Actor actorB)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = actorA.rect.x;
    rightA = leftA + actorA.image->w;
    topA = actorA.rect.y;
    bottomA = topA + actorA.image->h;

    leftB = actorB.rect.x;
    rightB = leftB + actorB.image->w;
    topB = actorB.rect.y;
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