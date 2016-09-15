#include "Human.h"
#include<random>
#include<ctime>
#include<glm\gtx\rotate_vector.hpp>
//#include"Zombie.h"
const float MIN_RUN = 300.0f;
Human::Human()
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos, int id)
{
	//randome engine
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randDir(0.01f, 1.0f);
	_health = 20.0f;
	_color = bengine::ColorRGBA8(233, 252, 3, 255);
	_speed = speed;
	_position = pos;
	_baraf = false;
	_id = id;
	//randomize direction
	_dir = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	//_direction 0 check
	if (_dir == glm::vec2(0.0f))
		_dir = glm::vec2(0.0f, 1.0f);
	_dir = glm::normalize(_dir);
	
}

void Human::update(const std::vector<std::string> &levelData,
	std::vector<Human*> &humans,
	float deltaTime)
{
	
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randRotate(-180.0f, 180.0f);
	_position += _dir * _speed * deltaTime;

	static float frames = 0.0f;
	glm::vec2 distVec;
	
	
	for (int i = 1; i < humans.size(); i++)
	{
		distVec = glm::vec2(humans[i]->getPos() - _position);
		if (humans[i]->getId() == _id)
			continue;
		
		if (glm::length(distVec) <= MIN_RUN && humans[i]->getBarafStatus() == true)
		{


			_dir = glm::vec2(glm::normalize(distVec));

			frames = 0.0f;

			collideWithLevel(levelData);
			return;
		}
		else if (glm::length(distVec) <= 100.0f && humans[i]->getBarafStatus() == false)
		{
			_dir = glm::vec2(-glm::normalize(distVec));

			frames = 0.0f;
			
			collideWithLevel(levelData);
			return;
		}
		glm::vec2 Hdist = glm::vec2(humans[0]->getPos() - _position);
		if (glm::length(Hdist) <= 200.0f)
		{
			_dir = glm::normalize(-glm::normalize(Hdist) + _dir);
		}
	}
		

	if (frames > 200.0f)
	{
		_dir = glm::rotate(_dir, randRotate(randomEngine));
		frames = 0.0f;
	}
	else
		frames+= (1.0f * deltaTime);
	
	if (collideWithLevel(levelData))
	{
		
		//_dir = -_dir;
		_dir = glm::rotate(_dir, randRotate(randomEngine));
	}
}
void Human::setBaraf()
{
	_speed = 0;
	_color = bengine::ColorRGBA8(153, 217, 234, 255);
	_baraf = true;
}

void Human::setUnBaraf()
{
	_speed = HUMAN_SPEED;
	_color = bengine::ColorRGBA8(233, 252, 3, 255);
	_baraf = false;
}