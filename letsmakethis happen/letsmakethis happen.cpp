// letsmakethis happen.cpp : Defines the entry point for the console application.
//


#include<Windows.h>
#include<SDL\SDL.h>
#include<GL\glew.h>
#include"MainGame.h"
#include<iostream>
//#include<GL/glew.h>


int main(int argc,char** argv)
{
	MainGame mainGame;
	mainGame.run();
	//int x;
	//std::cout << "fuck";
	//std::cin >> x;
    return 0;
}

