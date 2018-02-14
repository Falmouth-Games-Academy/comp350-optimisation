#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
{
	currentFrame = 0;
	maxFrames = 0;
	frameInc = 1;

	frameRate = 100; //Milliseconds
	oldTime = 0;

	oscillate = false;
}


Animation::~Animation()
{
}

//TODO: re-implemnt this to run the animation for a few seconds every few seconds
void Animation::addDelay(int delayTime, int animationRunTime)
{
	// if time has elapsed
	if (startTime <= SDL_GetTicks() - delayTime)
	{
		OnAnimate();
		if (startTime <= (SDL_GetTicks() - delayTime) + animationRunTime)
			startTime = SDL_GetTicks();
	}
}


void Animation::OnAnimate() 
{
	if (oldTime + frameRate > SDL_GetTicks()) {
		return;
	}

	oldTime = SDL_GetTicks();

	currentFrame += frameInc;

	if (oscillate) 
	{
		if (frameInc > 0) {
			if (currentFrame >= maxFrames) {
				frameInc = -frameInc;
			}
		}
		else {
			if (currentFrame <= 0) {
				frameInc = -frameInc;
			}
		}
	}
	else {
		if (currentFrame >= maxFrames) {
			currentFrame = 0;
		}
	}
}