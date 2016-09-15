#include "Agent.h"
#include<BENGINE\resourceManager.h>
#include"Lev.h"//for the tile width constant
#include<algorithm>
Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::checkTilePos(std::vector<glm::vec2> &CTP, float x, float y, const std::vector<std::string> &levelData)
{
	glm::vec2 cornerpos = glm::vec2(floor(x / (float)TILE_WIDTH), floor(y / (float)TILE_WIDTH));

	//check if outide the world
	if (cornerpos.x < 0 || cornerpos.x >= levelData[0].size() ||
		cornerpos.y < 0 || cornerpos.y >= levelData.size())
	{
		return;
	}
	if (levelData[cornerpos.y][cornerpos.x] != '.')
		CTP.push_back(cornerpos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
}

bool Agent::collideWithLevel(const std::vector<std::string> &levelData)
{

	//now we need to find the 4 tiles we gonna collide with
	std::vector<glm::vec2> collideTilePos;

	//check 4 corners

	//first corner
	checkTilePos(collideTilePos, _position.x, _position.y, levelData);
	//second
	checkTilePos(collideTilePos, _position.x + AGENT_WIDTH, _position.y, levelData);
	//third
	checkTilePos(collideTilePos, _position.x, _position.y + AGENT_WIDTH, levelData);
	//fourth
	checkTilePos(collideTilePos, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH, levelData);
	//do the thukraaavvvvvv
	if (collideTilePos.size() == 0)
		return false;
	for (int i = 0; i < collideTilePos.size(); i++)
		colideWithTile(collideTilePos[i]);
	return true;
}

bool Agent::collideWithAgent(Agent *agent)
{
	const float MIN_DIST = 2 * RADIUS_A;
	glm::vec2 centerPosA = _position + glm::vec2(RADIUS_A);
	glm::vec2 centerPosB = agent->_position + glm::vec2(RADIUS_A);
	glm::vec2 distVec = centerPosA - centerPosB;
	float distance = glm::length(distVec);
	float collisionDepth = MIN_DIST - distance;
	
	if (collisionDepth > 0)
	{
		glm::vec2 collisionVec = glm::normalize(distVec) * collisionDepth;
		_position += collisionVec / 2.0f;
		agent->_position -= collisionVec / 2.0f;//since we are in agent class we can ascess agent*'s privates too

		return true;
	}

	return false;
}
//AABB collision
void Agent::colideWithTile(glm::vec2 tilePos)
{
	
	
	const float RADIUS_T = (float)TILE_WIDTH / 2.0f;
	const float MIN_DIST = RADIUS_A + RADIUS_T;//max allowed dist
	//now i wont compare the distance vector magnitude with max allowed as it will result in the assumption
	//that the tile is also circular 
	//and we will go inside the corners 
	glm::vec2 centerPlayerPos = _position + glm::vec2(RADIUS_A);
	glm::vec2 distVec = centerPlayerPos - tilePos; //gets the distance vector between centers	   
	//x dir;
	float xDepth = MIN_DIST - abs(distVec.x);
	float yDepth = MIN_DIST - abs(distVec.y);//absolute value
	
	if (xDepth > 0 && yDepth > 0)
	{
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
			if (distVec.x < 0)
				_position.x -= xDepth;
			else
				_position.x += xDepth;
		else
			if (distVec.y < 0)
				_position.y -= yDepth;
			else
				_position.y += yDepth;
	}
}

void Agent::draw(bengine::spriteBatch &spriteBatch)
{

	glm::vec4 destRect = glm::vec4(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);//const because same for all

	//same texture for all so static
	static int textureID = bengine::resourceManager::getTexture("Textures/circle.png").id;
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

bool Agent::getDamaged(float damage)
{
	_health -= damage;
	_color.G += 20;
	if (_health <= 0)
		return true;
	else
		return false;
}