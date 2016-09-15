#pragma once
#include<GL\glew.h>
//this is structure for texture having unique id and dimensions
namespace bengine
{
	struct GLtexture
	{
		GLuint id;
		int width;
		int height;
	};

}