#pragma once
#include<vector>
//class for reading anyfile in as a buffer of bytes
namespace bengine
{
	class IOmanager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);//pass by ref for later filling //we use vector because it will be helpful later
	};

}