
#include "MainGame.h"
#include <bengine/Error.h>
#include<bengine/ImageLoader.h>
#include<BENGINE\bengine.h>
#include<BENGINE\resourceManager.h>


MainGame::MainGame() :
	_screenWidth(800),
	_screenHeight(800),
	_gameState(GameState::PLAY)

{
	_camera.init(_screenWidth, _screenHeight);
	//dnt erase :p constructor
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	/*_sprites.push_back(new bengine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, _screenWidth/2, _screenHeight/2, "textures/JimmyJump_Update 1.2/PNG/CharacterRight_Standing.png");
	_sprites.push_back(new bengine::Sprite());
	_sprites.back()->init(_screenWidth / 2, 0, _screenWidth / 2, _screenHeight / 2, "textures/JimmyJump_Update 1.2/PNG/Enemy_Snowman1.png");*/
	//_sprites.push_back(new bengine::Sprite());
	//_sprites.back()->init(0.0f, -01.0f, 1.0f, 1.0f, "textures/JimmyJump_Update 1.2/PNG/Enemy_Mushroom2.png");

	//_sprites.push_back(new bengine::Sprite());
	//_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "textures/JimmyJump_Update 1.2/PNG/Enemy_Broccoli2.png");

	gameLoop();
}

void MainGame::initSystems()
{
	bengine::init();
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(65.0f);

}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("shaders/colorShading.ver", "shaders/colorShading.frag");
	_colorProgram.addAttrib("vertexPosition");
	_colorProgram.addAttrib("vertexColor");
	_colorProgram.addAttrib("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();//for measuring ticks from top to bottom of this loop

		processInput();//processes any input

		

		_camera.update();
		
		for (int i = 0; i < _bullets.size(); )
		{
			if (_bullets[i].update() == true)//update returns true if the bullet die
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
				i++;
		}

		drawGame();
		//print every 10 average

		_fps = _fpsLimiter.end();
		static int fc = 0;
		fc++;
		if (fc == 10000)
		{
			std::cout << _fps << std::endl;
			fc = 0;
		}

	}
}

void MainGame::processInput()
{
	const float CAM_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
				break;

		}
	}
	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.ScrnToWorld(mouseCoords);
		
		glm::vec2 playePos(0.0f);
		glm::vec2 dir;//click dir
		dir = mouseCoords - playePos;
		dir = glm::normalize(dir);//converts dir to unit vector of that direction;

		_bullets.emplace_back(playePos, dir, 2.0f, 1000);
	}
	if(_inputManager.isKeyDown(SDLK_w))
		_camera.setPos(_camera.getPos() + glm::vec2(0.0f*CAM_SPEED, 1.0f*CAM_SPEED));
	if (_inputManager.isKeyDown(SDLK_s))
		_camera.setPos(_camera.getPos() + glm::vec2(0.0f*CAM_SPEED, -1.0f*CAM_SPEED));
	if (_inputManager.isKeyDown(SDLK_a))
		_camera.setPos(_camera.getPos() + glm::vec2(-1.0f*CAM_SPEED, 0.0f*CAM_SPEED));
	if (_inputManager.isKeyDown(SDLK_d))
		_camera.setPos(_camera.getPos() + glm::vec2(1.0f*CAM_SPEED, 0.0f*CAM_SPEED));
	if (_inputManager.isKeyDown(SDLK_q))
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	if (_inputManager.isKeyDown(SDLK_e))
		_camera.setScale(_camera.getScale() - SCALE_SPEED);

	
	
}

void MainGame::drawGame()
{
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//use color shader
	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	//get uniform from shader:
	//->sampler
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	//->camera matrix set up
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCamMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	
	//draw sprite
	_spriteBatch.begin();

	glm::vec4 destRect(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static bengine::GLtexture texture = bengine::resourceManager::getTexture("textures/JimmyJump_Update 1.2/PNG/CharacterRight_Standing.png");
	
	bengine::ColorRGBA8 color(255, 255, 255, 255);

	_spriteBatch.draw(destRect, uv, texture.id, 0.0f, color);
	/*_spriteBatch.draw(destRect + glm::vec4(50.0f, 0.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);
	_spriteBatch.draw(destRect + glm::vec4(0.0f, 50.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);
	_spriteBatch.draw(destRect + glm::vec4(50.0f, 50.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);*/
	
	for (int i = 0; i < _bullets.size(); i++)
		_bullets[i].draw(_spriteBatch);

	
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	//unuse color shader
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unUse();
	_window.swapBuff();
}

