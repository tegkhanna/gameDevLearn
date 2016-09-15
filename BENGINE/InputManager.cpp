#include "InputManager.h"


namespace bengine
{
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}



	void InputManager::pressKey(unsigned int keyId)
	{
		_keyMap[keyId] = true;
	}
	void InputManager::releaseKey(unsigned int keyId)
	{
		_keyMap[keyId] = false;
	}

	void InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyId)
	{
		auto it = _keyMap.find(keyId);
		if (it != _keyMap.end())
			return it->second;
		else
			return false;
	}
	void InputManager::update()
	{
		//sets previous equal to currennt. following statement is a "for each" loop c++ 11 and heigher 
		for (auto &it : _keyMap)
		{
			_previousKeyMap[it.first] = it.second;
		}
	}
	bool InputManager::isKeyPressed(unsigned int keyId)
	{
		if (isKeyDown(keyId) == true  && wasKeyDown(keyId) == false)
			return true;
		return false;
	}
	bool InputManager::wasKeyDown(unsigned int keyId)
	{
		auto it = _previousKeyMap.find(keyId);
		if (it != _previousKeyMap.end())
			return it->second;
		else
			return false;
	}
}