#include "Window.h"

#include "Error.h"
namespace bengine
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}


	int Window::create(std::string windowName, int screenW, int screenH, unsigned int currentF)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentF & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentF & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentF & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		//open openGL window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenW , screenH , flags);//makes this function make a window and set it to the pointer
		if (_sdlWindow == nullptr)//error check
			fatalError("teg u r an idiot 1(window)");

		//initialize SDL
		SDL_GLContext glContex = SDL_GL_CreateContext(_sdlWindow);
		if (glContex == nullptr)//error check
			fatalError("teg u r an idiot 2(glcontext)");

		//setup glew initialization
		glewExperimental = GL_TRUE;
		GLenum error = glewInit();
		if (error != GLEW_OK) // glew error check
			fatalError("teg u r idiot 3(glew init )");
		//check opengl version
		std::printf("*** OPENGL VERSION: %s ***\n", glGetString(GL_VERSION));

		//set bg color
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		SDL_GL_SetSwapInterval(1);//use 1 to activate vsynch

		//enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}


	void Window::swapBuff()
	{
		SDL_GL_SwapWindow(_sdlWindow);//swaps 2 frame
	}
}