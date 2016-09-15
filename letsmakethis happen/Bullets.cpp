
#include "Bullets.h"
#include<BENGINE\resourceManager.h>
#include<BENGINE\GLtexture.h>
#include<glm\glm.hpp>

Bullets::Bullets(glm::vec2 pos, glm::vec2 dir, float speed, float life):
	_pos(pos),
	_dir(dir),
	_speed(speed),
	_life(life)
{
}
Bullets::~Bullets()
{
}

void Bullets::draw(bengine::spriteBatch &spriteBatch)
{

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static bengine::GLtexture texture = bengine::resourceManager::getTexture("textures/JimmyJump_Update 1.2/PNG/CharacterRight_Standing.png");
	//bad but time pass :p
	bengine::ColorRGBA8 color(255, 255, 255, 255);
	glm::vec4 destBull = glm::vec4(_pos.x, _pos.y, 30, 30);
	spriteBatch.draw(destBull, uv, texture.id, 0.0f, color);

}

bool Bullets::update()
{
	_pos += _dir * _speed; //dir is gonna be unit vecot..so maths
	_life--;
	if (_life == 0)
		return true;//returns true at buyllet death
	return false;
}
