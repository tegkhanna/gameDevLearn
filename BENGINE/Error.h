

//error handling functions;- prints out error given as argument and then terminates
#pragma once
#include<string>
#include<GL\glew.h>
//this is not a class
namespace bengine
{
	extern void fatalError(std::string str, int x = 0);

}