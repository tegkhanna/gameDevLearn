#pragma once
#include<glm\glm.hpp>
#include<BENGINE\spriteBatch.h>
class Bullets
{
public:
	Bullets(glm::vec2 pos, glm::vec2 dir, float speed, float life);
	~Bullets();

	void draw(bengine::spriteBatch &spriteBatch);//tells the sprite batch to draw itselfm
	bool update();//returns true at buyllet death
private:
	float _life;
	float _speed;
	glm::vec2 _dir;
	glm::vec2 _pos;
};

