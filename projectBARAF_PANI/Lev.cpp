#include "Lev.h"
#include<fstream>
#include<iostream>
#include<BENGINE\Error.h>

#include<BENGINE\resourceManager.h>



Lev::Lev(const std::string &fileName)
{

	std::ifstream fin;
	fin.open(fileName.c_str(), std::ios::in);
	if (fin.fail())
		bengine::fatalError("failed to open " + fileName);
	std::string str;//first string throw away(first part contains faltu string, then number of humnas)
	fin >> str >> _numHuman;
	std::getline(fin, str);//throw away first line remains(\n)
	while (std::getline(fin, str))//read in vector each line for processing
	{
		_levelData.push_back(str);
	}
	int size = _levelData.size();
	std::string tmp;
	for (int i = 0; i < size / 2; i++)
	{
		tmp = _levelData[i];
		_levelData[i] = _levelData[size - i - 1];
		_levelData[size - i - 1] = tmp;
	}
	//tiles rendering begin
	_spriteBatch.init();
	_spriteBatch.begin();
	//render all tiles
	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			//grab tile
			char tile = _levelData[y][x];

			//get destRect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

			bengine::ColorRGBA8 whiteColor;
			whiteColor.R = 255; whiteColor.G = 255; whiteColor.B = 255; whiteColor.a = 255;
			//process tile
			switch (tile)
			{
			case 'R':
				_spriteBatch.draw(
					destRect,
					uvRect,
					bengine::resourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f,
					whiteColor);//drawn

				break;
			case '@':
				_levelData[y][x] = '.';// removes the player location after reading the player to prevent faltu collision 
				_startPlayerPos.x = x * TILE_WIDTH;
				_startPlayerPos.y = y * TILE_WIDTH;
				break;
			case '.':

				break;
			default:
				std::cout << "unexpected tile at (" << x << ", " << y << ") " << tile << std::endl;
				break;
			}
		}
	}
	_spriteBatch.end();
}


Lev::~Lev()
{
}

void Lev::draw()
{
	_spriteBatch.renderBatch();
}