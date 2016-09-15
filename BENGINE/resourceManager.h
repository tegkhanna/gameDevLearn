#pragma once
#include"GLtexture.h"
#include"textureCache.h"
#include<string>
//manages the available resources
namespace bengine
{
	class resourceManager
	{
	public:

		static GLtexture getTexture(std::string filePath);//returns a gl texture



	private:
		static textureCache _textureCache;//object of cache class for the texture 
	};

}