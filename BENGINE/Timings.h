#pragma once
#include<GL\glew.h>
namespace bengine
{
	class FpsLimiter
	{
	public:
		FpsLimiter();
		void init(float targetFps);
		void setMaxFps(float targetFps);
		void begin();
		float end();//end returns fps
		
	private:
		void calcFPS();
		float _fps;
		float _frameTime;
		float _maxFps;
		GLuint _startTicks;
	};
}