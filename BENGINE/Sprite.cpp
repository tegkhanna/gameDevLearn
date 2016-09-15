
#include "Sprite.h"
#include"Vertex.h"
#include"resourceManager.h"
#include<cstddef>

namespace bengine
{
	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0)
			glDeleteBuffers(1, &_vboID);

	}


	void Sprite::init(float x, float y, float width, float height, std::string texPath)
	{

		_x = x;
		_y = y;
		_height = height;
		_width = width;
		_texture = resourceManager::getTexture(texPath);


		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);

		}

		Vertex vertexData[6];
		//first triangle
		vertexData[0].setPos(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPos(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPos(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//second triangle

		vertexData[3].setPos(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPos(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPos(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		//color setting
		for (int i = 0; i < 6; i++)
		{
			vertexData[i].setColor(255, 0, 255, 255);
		}

		//fun change
		vertexData[1].setColor(0, 255, 0, 255);

		vertexData[4].setColor(0, 0, 255, 255);




		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//bind buffer obj
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//tell opengl that we wanna use the first attribute array
		//we only need one array right now since we only usee posn
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//posn attrib pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));//the last 0 tells the position is at the first byte(0)/
		//instead we use offsetof for the first byte of structure

		//color attrib//1 for second attrib
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));//offset returns 8

		//UV attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//draw 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//disable vertex attrib array
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);


		//unbind vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
