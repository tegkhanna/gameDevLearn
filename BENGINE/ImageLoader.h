#pragma once
#include"GLtexture.h"

#include<string>
//class reads the image in as a buffer of bytes for processing by picoPng
namespace bengine
{
	class ImageLoader
	{

	public:
		static GLtexture loadPNG(std::string filePath);
	};
}