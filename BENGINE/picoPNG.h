#pragma once
#include"stdafx.h"

#include<vector>//picoPNG function to read a png image to texture
namespace bengine
{
	int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

}