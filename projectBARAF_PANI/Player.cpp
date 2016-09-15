#include "Player.h"
#include<SDL\SDL.h>
//#include"Gun.h"
//#include"Bullet.h"
Player::Player():
	_zombieKilled(0),
	_currGunIndex(-1)
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position, bengine::InputManager *inputManager, bengine::camera2D *camera)
{
	_health = 150.0f;
	
	_camera = camera;
	_speed = speed;
	_position = position;
	_color = bengine::ColorRGBA8(0, 0, 150, 255);
	_inputManager = inputManager;
}
void Player::update(const std::vector<std::string> &levelData,
					std::vector<Human*> &humans,
					float deltaTime)
{
	if (_inputManager->isKeyDown(SDLK_w) && _inputManager->isKeyDown(SDLK_d))
	{
		_dir = glm::vec2(1, 1);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_s) && _inputManager->isKeyDown(SDLK_d))
	{
		_dir = glm::vec2(1, -1);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_w) && _inputManager->isKeyDown(SDLK_a))
	{
		_dir = glm::vec2(-1, 1);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_s) && _inputManager->isKeyDown(SDLK_a))
	{
		_dir = glm::vec2(-1, -1);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_w))
	{
		_dir = glm::vec2(0, 1);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_s))
	{
		_dir = glm::vec2(0, -1);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_a))
	{
		_dir = glm::vec2(-1, 0);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}
	else if (_inputManager->isKeyDown(SDLK_d))
	{
		_dir = glm::vec2(1, 0);
		_dir = glm::normalize(_dir);
		_position += (_speed * _dir * deltaTime);
	}

	//if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 0)
	//	_currGunIndex = 0;
	//else if (_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1)
	//	_currGunIndex = 1;
	//else if (_inputManager->isKeyDown(SDLK_3) && _guns.size() >= 2)
	//	_currGunIndex = 2;
	//else if (_inputManager->isKeyDown(SDLK_4) && _guns.size() >= 3)
	//{
	//	if(_zombieKilled >= 150)
	//		_currGunIndex = 3;
	//}
	//
	//if (_currGunIndex != -1)
	//{

	//	glm::vec2 mouseCoord = _inputManager->getMouseCoords();
	//	mouseCoord = _camera->ScrnToWorld(mouseCoord);
	//	glm::vec2 playerCenter = _position + glm::vec2(RADIUS_A - 5);
	//	glm::vec2 fireDir = glm::normalize(mouseCoord - playerCenter);
	//	//_guns[_currGunIndex]->update(_inputManager->isKeyDown(SDL_BUTTON_LEFT),
	//	//							playerCenter,
	//	//							fireDir, *_bullets, deltaTime);
	//}
	collideWithLevel(levelData);

}

//void Player::addGun(Gun *gun)
//{
//	_guns.push_back(gun);
//
//	//if no gun equiped..then equip
//	if (_currGunIndex == -1)
//		_currGunIndex = 0;
//}