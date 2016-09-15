#include<SDL\SDL.h>
#include<GL\glew.h>
#include"bengine.h"

namespace bengine
{
	int init()
	{
		//initialize sd
		SDL_Init(SDL_INIT_EVERYTHING);//initialize sdl

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//removes flickering

		return 0;
	}
}