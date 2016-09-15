#pragma once
#include<map>
#include"GLtexture.h"
//texture chaching class
namespace bengine
{
	class textureCache
	{
	public:
		textureCache();
		~textureCache();
		GLtexture getTexture(std::string texturePath);//  loads texture

	private:
		std::map<std::string, GLtexture> _textureMap;//a map(sorted vector like) for textures takes in 1)path 2)and a texture object(unique id)

	};

}