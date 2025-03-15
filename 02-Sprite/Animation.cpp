#include "Animation.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y)
{
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		// Don't update frame if animation is finished (non-looping and at last frame)
		if (!isLooping && currentFrame == frames.size() - 1)
		{
			// Just continue showing the last frame
		}
		else
		{
			DWORD t = frames[currentFrame]->GetTime();
			if (now - lastFrameTime > t)
			{
				currentFrame++;
				lastFrameTime = now;

				// Handle end of animation differently based on looping flag
				if (currentFrame == frames.size())
				{
					if (isLooping)
						currentFrame = 0;  // Loop back to start
					else
						currentFrame = frames.size() - 1;  // Stay on last frame
				}
			}
		}
	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}
