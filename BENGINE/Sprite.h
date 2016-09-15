#pragma once
#include<GL\glew.h>
#include"GLtexture.h"
#include<string>
//sprite class
namespace bengine
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		void init(float x, float y, float width, float height, std::string texPath);
		/*initializes a sprite
		1)X coord
		2)y coor
		3)width
		4)height
		5)path of texture
		
		*/

		void draw();//draws on screen

	private:
		int _x;
		int _y;
		int _width;
		int _height;

		GLuint _vboID;//id of the sprite
		GLtexture _texture;//texture

	};

}