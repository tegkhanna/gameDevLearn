
#include"Error.h"
#include<iostream>
#include<SDL\SDL.h>
#include<process.h>
//prints fatal error

namespace bengine
{
	void fatalError(std::string str, int x /*=0*/)//x is to check weather need to pause or not
	{
		std::cout << str << std::endl;
		if (x == 0)
		{
			std::cout << "enter any no. to quit";
			int x;
			std::cin >> x;
		}
		SDL_Quit();
		exit(1);

	}
}