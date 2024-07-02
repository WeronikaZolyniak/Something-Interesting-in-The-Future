#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Actor.h"
#include"Vector.h"
#include "Audio.h"

bool UpdateActorPosition(Actor &actor, Vector2 vector, Actor Walls[21]);
bool UpdateActorMovement(Actor &actor, Vector2 vector, Actor Walls[21]);
void ChangePointLocation(Actor &Point, Actor Walls[21]);
void UpdateOctopusPosition(uint32_t deltaTime, Actor& Octopus, Actor& Turtle, Actor Walls[21]);
void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, Actor Walls[21]);