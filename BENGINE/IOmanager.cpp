
#include "IOmanager.h"
#include<fstream>
namespace bengine
{
	bool IOmanager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		//trick to find file size
		file.seekg(0, std::ios::end); //go to end
		int fileSize = file.tellg(); // tell byte position= current location
		file.seekg(0, std::ios::beg);// back to begining to read

		buffer.resize(fileSize);//resize vector
		file.read((char*)&buffer[0], fileSize);// reads the given no. of bytes(Second para) to the buffer
		file.close();

		return true;


	}
}