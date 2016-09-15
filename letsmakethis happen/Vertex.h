#pragma once
#include"stdafx.h"
#include<GL\glew.h>

struct Color
{
	GLubyte R;
	GLubyte G;
	GLubyte B;
	GLubyte a;//alpha
};
struct Position
{
	float x;
	float y;
};

struct UV
{
	float u;
	float v;
};

struct Vertex
{
	Position position;
	
	//RGB alpha(transparency
	Color color;
	
	//we use glbyte(similar to unsigned char can take upto 255 and makes small size
	//4 byte multiple stable
	UV uv;

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.R = r;
		color.G = g;
		color.B = b;
		color.a = a;
	}
	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}

	void setPos(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

};