#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Audio.h"
#include "Actor.h"

void PlayActorSound(Actor actor)
{
	if (Mix_Playing(1) == 0) Mix_PlayChannel(1, actor.walkSound, 0);
}

void StopSound(int channel)
{
	if (Mix_Playing(channel) != 0) Mix_HaltChannel(channel);
}