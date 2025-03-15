#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"


using namespace std;

class CAnimation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool isLooping;  // Flag to control looping behavior
public:
	CAnimation(int defaultTime, bool looping = true) {
		this->defaultTime = defaultTime;
		lastFrameTime = -1;
		currentFrame = -1;
		isLooping = looping;
	}
	void Add(int spriteId, DWORD time = 0);

	void Render(float x, float y);
	// Add this method to Animation.h file
	void RenderFrame(int frameIndex, float x, float y)
	{
		if (frameIndex >= 0 && frameIndex < frames.size()) {
			frames[frameIndex]->GetSprite()->Draw(x, y);
		}
	}

	//Handle looping
	void SetLooping(bool looping) { this->isLooping = looping; }
	bool IsLooping() { return isLooping; }
	bool IsFinished() { return !isLooping && currentFrame == frames.size() - 1; }

	//Reset the animation
	void Reset() { currentFrame = -1; lastFrameTime = -1; }
};

typedef CAnimation* LPANIMATION;
