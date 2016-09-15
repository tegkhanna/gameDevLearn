
#pragma once
#include<vector>
#include<string>
#include<BENGINE/spriteBatch.h>
const int TILE_WIDTH = 64;
class Lev
{

public:
	Lev(const std::string &fileName);//constructor loads the level
	~Lev();
	void draw();

	//getters
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }
	int getHumansNum() const { return _numHuman; }
	glm::vec2 getPlayerStart() const { return _startPlayerPos; }
	const std::vector<std::string> &getLevelData() const { return _levelData; }
private:
	int _numHuman;
	std::vector<std::string> _levelData;
	bengine::spriteBatch _spriteBatch;
	glm::vec2 _startPlayerPos;
};

