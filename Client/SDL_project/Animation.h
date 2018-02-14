#pragma once
class Animation
{
public:
	Animation();
	~Animation();

	int maxFrames;
	bool oscillate;

	void OnAnimate();

	int setFrameRate(int newFrameRate) { return frameRate = newFrameRate; }
	int setCurrentFrame(int newFrame) { return currentFrame = newFrame; }
	int getCurrentFrame() { return currentFrame; }

	void addDelay(int delayTime, int animationRunTime);

private:
	int currentFrame;
	int frameInc;
	int frameRate;
	long oldTime;
	int startTime;
};

