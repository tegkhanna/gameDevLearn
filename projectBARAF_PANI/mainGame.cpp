#include "mainGame.h"

#include "MainGame.h"
#include<random>
#include<ctime>
#include<algorithm>
#include <Bengine/Bengine.h>
#include<BENGINE\Timings.h>
#include<BENGINE\Error.h>
#include <SDL/SDL.h>
#include <iostream>
int ids = 1; // to give individual ids to each human(had a sudden need for this ...just initialized it globally because i was being a lazy ass)
mainGame::mainGame() :
	_screenW(800),
	_screenH(800),
	_gameState(GameState::PLAY),
	_fps(0.0f),
	_level(nullptr)
{

}


mainGame::~mainGame()
{
}

void mainGame::run()
{
	initSystems();
	initLevel();
	bengine::Music gameMusic = _audioEngine.loadMusic("Sound/try.ogg");
	gameMusic.play();
	gameLoop();
}

void mainGame::run2()
{

	initLevel();
	bengine::Music gameMusic = _audioEngine.loadMusic("Sound/try.ogg");
	gameMusic.play();
	gameLoop();
}
void mainGame::initSystems()
{
	// IMPLEMENT THIS!
	bengine::init();
	_audioEngine.init();
	_window.create("try", _screenW, _screenH, 0);
	glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
	initShaders();
	_agentSB.init();
	_hudSpriteBatch.init();
	_pauseSpriteBatch.init();
	//inititalize sprite font
	_spriteFont = new bengine::SpriteFont("Fonts/OpenSans-Semibold.ttf", 64);

	//initialize cam
	_hudCamera.init(_screenW, _screenH);
	_hudCamera.setPos(glm::vec2(_screenW / 2.0f, _screenH / 2.0f));
	_camera.init(_screenW, _screenH);
	_camera.setPos(glm::vec2(_screenW / 2, (_screenH / 2)-100));
	_camera.setScale(0.50f);
	_barfSound = _audioEngine.loadSoundEffect("Sound/baraf.wav");
	_paniSound = _audioEngine.loadSoundEffect("Sound/pani.wav");

}

void mainGame::initLevel()
{
	_level = new Lev("Levels/level6.txt");
	_player = new Player;
	_player->init(10.0f, _level->getPlayerStart(), &_inputManager,&_camera);
	_player->setId(ids++);
	_humans.push_back(_player);

	//add rtandome humans
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randX(2, _level->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _level->getHeight() - 2);

	for (int i = 0; i < _level->getHumansNum(); i++)
	{
		_humans.push_back(new Human);
		_humans.back()->init(HUMAN_SPEED, //speed
			glm::vec2(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH),//random pos
			ids++);

	}

}


void mainGame::initShaders()
{
	_textureProgram.compileShaders("Shaders/textureShading.ver", "Shaders/textureShading.frag");
	_textureProgram.addAttrib("vertexPosition");
	_textureProgram.addAttrib("vertexColor");
	_textureProgram.addAttrib("vertexUV");
	_textureProgram.linkShaders();
}

void mainGame::gameLoop()
{

	bengine::FpsLimiter fpsLimitter;
	fpsLimitter.setMaxFps(60.0f);
	
	const int MAX_STEPS = 6;
	const float MS_PER_SEC = 1000.0f;
	const float DESIRED_FPS = 60.0f;
	const float DESIRED_FRAME_TIME = MS_PER_SEC / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;
	float previousTicks = SDL_GetTicks();
	while (_gameState != GameState::EXIT)
	{
		///>SUPER SMARTTTTTTTTT SUPER DUPER :P // MAINTAINS A CONSTANT GAME SPEED IRRESPECTIVE OF THE FPS
		fpsLimitter.begin();
		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAME_TIME;
		_inputManager.update();
		processInput();
		if (_inputManager.isKeyPressed(SDLK_p))
		{
			_gameState = GameState::PAUSE;

		}

		if (_gameState != GameState::PAUSE)
		{

			int i = 0;
			while (totalDeltaTime > 0 && i++ < MAX_STEPS)
			{
				float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
				updatePlayer(deltaTime);
				updateTime(deltaTime);
				if (_timeRemain <= 0)
				{
					_loose = true;
					_gameState = GameState::PAUSE;
				}
				totalDeltaTime -= deltaTime;
			}
		}

		_camera.setPos(glm::vec2(_player->getPos().x, _player->getPos().y));

		_camera.update();
		_hudCamera.update();
		drawGame();
		_fps = fpsLimitter.end();
		static int frames = 0;
		if (frames == 1000)
		{
			std::cout << _fps << std::endl;
			frames = 0;
		}
		else
			frames++;
	}
	if (_gameState == GameState::EXIT)
	{
		bengine::fatalError("bye bye .. thanks for playing :D :D :D", 1);
	}

}
void mainGame::updateTime(float deltaTime)
{
	static int see = 0;
	see++;
	if (see == _MAX_FPS)
	{
		_timeRemain = _timeRemain - deltaTime;
		see = 0;
	}

}
void mainGame::updatePlayer(float delta)
{
	//humans update
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_level->getLevelData(), _humans, delta);
	}


	//collision
	for (int i = 0; i < _humans.size(); i++)
	{
		for (int j = 1; j < _humans.size(); j++)
		{
			if (j == i)
				continue;
			if (i == 0 && _humans[i]->collideWithAgent(_humans[j]) && _humans[j]->getBarafStatus() == false)
			{
				_humans[j]->setBaraf();
				_barafed++;
				_barfSound.play();

				if (_barafed == _humans.size() - 1)
				{
					_win = true;
					_gameState = GameState::PAUSE;
				}
			}
			else
			{
				if (i != 0 && _humans[i]->collideWithAgent(_humans[j]) && _humans[j]->getBarafStatus() == true)
				{
					_humans[j]->setUnBaraf();
					_barafed--;
					_paniSound.play();
				}
			}
		}
	}

}

void mainGame::drawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);
	//get uniform from shader:
	//->sampler
	GLint textureLocation = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	//->camera matrix set up
	GLuint pLocation = _textureProgram.getUniformLocation("P");//location
															   //grab camera matrix
	glm::mat4 cameraMatrix = _camera.getCamMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//draw

	_level->draw();

	const glm::vec2 agentDim(RADIUS_A * 2.0f);
	//draw agents(including player)
	_agentSB.begin();
	//draw humans
	for (int i = 0; i < _humans.size(); i++)
	{
		if (_camera.isInViewBox(_humans[i]->getPos(), agentDim))
			_humans[i]->draw(_agentSB);
	}

	_agentSB.end();

	_agentSB.renderBatch();
	drawHud();
	if (_gameState == GameState::PAUSE && _win == false && _loose == false)
	{
		drawPause();
		if (_inputManager.isKeyPressed(SDLK_1) || _inputManager.isKeyPressed(SDLK_KP_1))
			_gameState = GameState::PLAY;
		if (_inputManager.isKeyPressed(SDLK_2) || _inputManager.isKeyPressed(SDLK_KP_2))
			_gameState = GameState::EXIT;
		if (_inputManager.isKeyPressed(SDLK_3) || _inputManager.isKeyPressed(SDLK_KP_3))
		{
			_gameState = GameState::PLAY;
			run2();
		}
	}
	else if (_gameState == GameState::PAUSE && _win == true)
	{
		drawPause();
		if (_inputManager.isKeyPressed(SDLK_1) || _inputManager.isKeyPressed(SDLK_KP_1))
			_gameState = GameState::EXIT;
	}
	else if (_gameState == GameState::PAUSE && _loose == true)
	{
		drawPause();
		if (_inputManager.isKeyPressed(SDLK_1) || _inputManager.isKeyPressed(SDLK_KP_1))
			_gameState = GameState::EXIT;
	}
	_textureProgram.unUse();
	// Swap our buffer and draw everything to the screen!
	_window.swapBuff();
}
void mainGame::processInput()
{
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			// Exit the game here!
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
}


void mainGame::drawHud()
{
	char buffer[256];

	//setup camera matrix

	GLuint pLocation = _textureProgram.getUniformLocation("P");//location
															   //grab camera matrix
	glm::mat4 cameraMatrix = _hudCamera.getCamMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_hudSpriteBatch.begin();
	//add text to screen
	sprintf_s(buffer, "players total: %d", _humans.size() - 1);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0.0f, 80.0f), glm::vec2(0.5f), 0.0f, bengine::ColorRGBA8(233, 252, 3, 255));
	sprintf_s(buffer, "humans barafed: %d", _barafed);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0.0f, 50.0f), glm::vec2(0.5f), 0.0f, bengine::ColorRGBA8(153, 217, 234, 255));
	sprintf_s(buffer, "humans left : %d", _humans.size() - 1 - _barafed);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(500.0f, 80.0f), glm::vec2(0.5f), 0.0f, bengine::ColorRGBA8(233, 252, 3, 255));
	sprintf_s(buffer, "Press P to pause");
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(300.0f, 10.0f), glm::vec2(0.3f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));
	sprintf_s(buffer, "time: %d", _timeRemain);
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(300.0f, 700.0f), glm::vec2(0.3f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));
	_hudSpriteBatch.end();
	_hudSpriteBatch.renderBatch();
}
///<PAUSE
void mainGame::drawPause()
{
	char buffer[256];
	if (!_win && !_loose)
	{//uses hud camera
	//add text to screen
		sprintf_s(buffer, "GAME PAUSED");
		_spriteFont->draw(_pauseSpriteBatch, buffer, glm::vec2(270.0f, 400.0f), glm::vec2(0.75f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));
		sprintf_s(buffer, "PRESS 1 TO CONTINUE");
		_spriteFont->draw(_pauseSpriteBatch, buffer, glm::vec2(180.0f, 300.0f), glm::vec2(0.75f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));
		sprintf_s(buffer, "PRESS 2 TO EXIT");
		_spriteFont->draw(_pauseSpriteBatch, buffer, glm::vec2(230.0f, 200.0f), glm::vec2(0.75f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));

		_pauseSpriteBatch.end();
		_pauseSpriteBatch.renderBatch();
	}
	else if(_win)
	{
		sprintf_s(buffer, "YOU WIN!!!!!!!");
		_spriteFont->draw(_pauseSpriteBatch, buffer, glm::vec2(270.0f, 300.0f), glm::vec2(0.75f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));
		_pauseSpriteBatch.end();
		_pauseSpriteBatch.renderBatch();
	}
	else if (_loose)
	{
		sprintf_s(buffer, "TIME OVER BITCHES.. YOU LOOSE!!");
		_spriteFont->draw(_pauseSpriteBatch, buffer, glm::vec2(10.0f, 300.0f), glm::vec2(0.75f), 0.0f, bengine::ColorRGBA8(0, 0, 0, 255));
		_pauseSpriteBatch.end();
		_pauseSpriteBatch.renderBatch();
	}
}
