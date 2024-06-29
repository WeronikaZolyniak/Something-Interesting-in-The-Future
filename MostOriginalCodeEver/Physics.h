#pragma once
#include <SDL.h>
#include <iostream>
#include "Actor.h"
#include"Vector.h"
#include "Audio.h"

void UpdateActorPosition(Actor &actor, Vector2 vector, Actor &Wall);
void UpdateActorMovement(Actor &actor, Vector2 vector, Actor &Wall);
void ChangePointLocation(Actor &Point, Actor &Wall);
void UpdateOctopusPosition(uint32_t deltaTime, Actor &Octopus, Actor &Turtle, Actor &Wall);
void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, Actor &Wall);