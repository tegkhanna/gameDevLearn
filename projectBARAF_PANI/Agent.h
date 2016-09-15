#pragma once
#include<glm\glm.hpp>
#include<BENGINE\spriteBatch.h>
const float AGENT_WIDTH = 60.0f;
const float RADIUS_A = (float)AGENT_WIDTH / 2.0f;

class Human; //forward declareation to prevent using header and thus preventing circular includes
class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string> &levelData,
						std::vector<Human*> &humans,
						float deltaTime) = 0; //tells that all derived class will have this update function and thisbase class cannot

	bool collideWithLevel(const std::vector<std::string> &levelData);
	void checkTilePos(std::vector<glm::vec2> &CTP, float x, float y, const std::vector<std::string> &levelData);//ctp->collide tile pos
	void colideWithTile(glm::vec2 tilePos);
	bool collideWithAgent(Agent *agent);
	bool getDamaged(float damage);
	void draw(bengine::spriteBatch &spriteBatch);

	//getters
	glm::vec2 getPos() const { return _position; }
protected:
	glm::vec2 _position;
	float _speed;
	float _health;
	glm::vec2 _dir;
	bengine::ColorRGBA8 _color;

};

