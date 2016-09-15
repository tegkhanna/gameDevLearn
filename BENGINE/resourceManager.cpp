
#include "resourceManager.h"

namespace bengine
{
	textureCache resourceManager::_textureCache;

	GLtexture resourceManager::getTexture(std::string filePath)
	{
		return _textureCache.getTexture(filePath);
	}
}