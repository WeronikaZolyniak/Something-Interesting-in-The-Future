#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Actor.h"
#include"Vector.h"
#include "Audio.h"

bool UpdateActorPosition(Actor &actor, Vector2 vector, int Walls[12][16]);
bool UpdateActorMovement(Actor &actor, Vector2 vector, int Walls[12][16]);
void ChangePointLocation(Actor &Point, int Walls[12][16]);
void UpdateOctopusPosition(uint32_t deltaTime, Actor& Octopus, int Walls[12][16]);
void UpdateTurtlePosition(uint32_t deltaTime, Vector2 &InputVector, Actor &Turtle, int Walls[12][16]);