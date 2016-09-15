#pragma once
#include<glm\glm.hpp>
#include<unordered_map>
namespace bengine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		void update();
		void pressKey(unsigned int keyId);
		void releaseKey(unsigned int keyId);

		bool isKeyDown(unsigned int keyId);
		bool isKeyPressed(unsigned int keyId);

		void setMouseCoords(float x, float y);

		//getters
		glm::vec2 getMouseCoords() const { return _mouseCoords; }//const because it seems right as no change in class occur
	private:
		bool wasKeyDown(unsigned int keyId);
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoords;
	
	
	};

}