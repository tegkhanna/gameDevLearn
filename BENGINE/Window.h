#pragma once
#include<SDL\SDL.h>
#include<GL\glew.h>
#include<string>
//creates a window from the engine
namespace bengine
{
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };//no class because we gonna use bitwise operator
	//flags
	class Window
	{
	public:
		Window();
		~Window();
		void swapBuff();//swaps the windows
		int create(std::string windowName, int screenW, int screenH, unsigned int currentF);//create a window
		int getScreenW() { _screenW; }
		int getScreenH() { _screenH; }

	private:
		SDL_Window * _sdlWindow;
		int _screenW, _screenH;
	};

}