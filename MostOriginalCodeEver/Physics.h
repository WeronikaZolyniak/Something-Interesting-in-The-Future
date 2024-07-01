#pragma once
#include <SDL.h>
#include <iostream>
#include "Actor.h"
#include"Vector.h"
#include "Audio.h"

void UpdateActorPosition(Actor &actor, Vector2 vector, Actor Walls[20]);
void UpdateActorMovement(Actor &actor, Vector2 vector, Actor Walls[20]);
void ChangePointLocation(Actor &Point, Actor Walls[20]);
void UpdateOctopusPosition(uint32_t deltaTime, Actor &Octopus, Actor &Turtle, Actor Walls[20]);
void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, Actor Walls[20]);