#pragma once
#include<SDL\SDL.h>
#include<gl\glew.h>
#include<iostream>
#include<BENGINE/camera2D.h>
#include<bengine/GLSLprog.h>
#include<bengine/Sprite.h>
#include<bengine/GLtexture.h>
#include<vector>
#include<BENGINE/Window.h>
#include<BENGINE\spriteBatch.h>
#include<BENGINE\InputManager.h>
#include<BENGINE\Timings.h>
#include"Bullets.h"
enum class GameState { PLAY, EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();//runs the system
	
	

private:
	//initializers
	void initSystems();//starts the system
	void gameLoop();//main game loop
	void processInput();//input processing..clicks and motions
	void drawGame();//draw the frame
	void initShaders();//initialize the shaders

	
	int _screenWidth;//screen dimensions
	int _screenHeight;
	float _fps;
	GameState _gameState;
	bengine::Window _window;//pointer to a window(set default to nullptr) 
	//std::vector<bengine::Sprite*> _sprites; // we use pointers because with array, the buffer gets deleted again n again .. so sprites are copied and deleted which destroys their data(because of its destructor).
									// so instead we store it in the heap memory. therefore only pointers are copied and deleted, no the actual sprite
	bengine::camera2D _camera;
	bengine::GLSLprog _colorProgram;
	bengine::spriteBatch _spriteBatch;
	bengine::InputManager _inputManager;
	bengine::FpsLimiter _fpsLimiter;
	std::vector<Bullets> _bullets;
};

