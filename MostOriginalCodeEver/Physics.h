#pragma once
#include <SDL.h>
#include <iostream>
#include "Actor.h"
#include"Vector.h"
#include "Audio.h"


void UpdateActorPosition(Actor &actor, Vector2 vector);
void UpdateActorMovement(Actor &actor, Vector2 vector);
void ChangePointLocation(Actor &Point);
void UpdateOctopusPosition(uint32_t deltaTime, Actor &Octopus, Actor &Turtle);
void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle);