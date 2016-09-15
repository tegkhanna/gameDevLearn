
#include "textureCache.h"
#include"ImageLoader.h"
#include<iostream>
namespace bengine
{
	textureCache::textureCache()
	{
	}


	textureCache::~textureCache()
	{
	}


	GLtexture textureCache::getTexture(std::string texturePath)
	{
		//lookup the map
		auto mit = _textureMap.find(texturePath);//std::map<std::string, GLtexture>::iterator smart compiler automatically dows this

		//check if not
		if (mit == _textureMap.end())
		{
			//load the texture/image
			GLtexture newTexture = ImageLoader::loadPNG(texturePath);



			_textureMap.insert(make_pair(texturePath, newTexture));//insert takes a pair std::pair<std::string, GLtexture> newPair(texturePath, newTexture);
			//make_pair makes the job easier
			
			return newTexture;
		}
		
		return mit->second;//second returns second part of pair: here texture


	}
}