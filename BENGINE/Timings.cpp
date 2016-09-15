#include"Timings.h"
#include<SDL\SDL.h>
namespace bengine
{
	FpsLimiter::FpsLimiter()
	{

	}
	void FpsLimiter::init(float targetFps)
	{
		setMaxFps(targetFps);
	}
	void FpsLimiter::setMaxFps(float targetFps)
	{
		_maxFps = targetFps;
	}
	void FpsLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}
	float FpsLimiter::end()
	{
		calcFPS();
		float frameTicks = SDL_GetTicks() - _startTicks;
		//limitter
		if (1000.0f / _maxFps > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFps - frameTicks);
		}
		return _fps;
	}

	void FpsLimiter::calcFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;
		static float prevTicks = SDL_GetTicks();
		float currentTicks = SDL_GetTicks();
		_frameTime = currentTicks - prevTicks;
		prevTicks = SDL_GetTicks();
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

		int count;
		currentFrame++;
		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
			count = NUM_SAMPLES;

		float ftAverage = 0;
		for (int i = 0; i < count; i++)
		{
			ftAverage += frameTimes[i];
		}

		if (count != 0)
			ftAverage = ftAverage / count;
		if (ftAverage != 0)
			_fps = 1000.0f / ftAverage;
		else
			_fps = 0;

	}
	
}
