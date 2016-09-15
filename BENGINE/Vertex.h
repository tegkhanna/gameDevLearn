#pragma once
#include"stdafx.h"
#include<GL\glew.h>
namespace bengine
{
	struct ColorRGBA8
	{
		ColorRGBA8():R(0), G(0), B(0), a(255){}
		ColorRGBA8(GLubyte r, GLubyte g, GLubyte b, GLubyte A = 255) :R(r), G(g), B(b), a(A) {}
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
		ColorRGBA8 color;

		//we use glbyte(similar to unsigned char can take upto 255 and makes small size
		//4 byte multiple stable
		UV uv;

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color = ColorRGBA8(r, g, b, a);
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
}