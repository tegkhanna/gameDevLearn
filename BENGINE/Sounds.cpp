#include "Sounds.h"
#include"Error.h"
namespace bengine
{

	Sounds::Sounds()
	{
	}


	Sounds::~Sounds()
	{
		destroy();
	}


	void SoundEffect::play(int loops/*=0*/)
	{
		if (Mix_PlayChannel(-1, _chunk, loops) == -1) // loops -1 = infinite, 0= once, 1 = 2 and so on
		{
			if(Mix_PlayChannel(0, _chunk, loops) == -1)
				fatalError("Mix_PlayChannel: " + std::string(Mix_GetError()));
		}
	}

	void Music::play(int loops/*=-1*/)
	{
		if (Mix_PlayMusic( _music, loops) == -1) // -1 = infinite ,loops 0 = 0, 1= once, 2 = 2 and so on
		{
				fatalError("Mix_PlayMusic: " + std::string(Mix_GetError()));
		}
	}


	void Music::pause()
	{
		Mix_PauseMusic();
	}
	void Music::resume()
	{
		Mix_ResumeMusic();
	}
	void Music::stop()
	{
		Mix_HaltMusic();
	}




	void Sounds::init()
	{
		//pre build inititalizer
		//parameters: MIX_INIT_FAC,MIX_INIT_MOD, MIX_INIT_MP3 and ogg
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) // -1 means an error
		{
			fatalError("Mix_Init error: " + std::string(Mix_GetError()));///Mix_GetError returns a c string to the last error <We use std::string wrapper to convert the csting to string type>
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
		}
		_isInitialised = true;
	}
	void Sounds::destroy()
	{
		if (_isInitialised)
		{
			_isInitialised = false;
			Mix_Quit();
		}
	}


	void Sounds::play()
	{

	}

	SoundEffect Sounds::loadSoundEffect(const std::string &filePath)
	{
		//try to find the audio in cache
		SoundEffect effect;
		auto it = _effectMap.find(filePath);
		//check if not found
		if (it == _effectMap.end())
		{
			//if not found then create
			Mix_Chunk *chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr)
			{
				//check error
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
			}

			_effectMap[filePath] = chunk;
			effect._chunk = chunk;

		}
		else
		{
			effect._chunk = it->second;
		}
		return effect;
	}
	Music Sounds::loadMusic(const std::string &filePath)
	{
		//try to find the audio in cache
		Music effect;
		auto it = _musicMap.find(filePath);
		//check if not found
		if (it == _musicMap.end())
		{
			//if not found then create
			Mix_Music *music = Mix_LoadMUS(filePath.c_str());
			if (music == nullptr)
			{
				//check error
				fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
			}

			_musicMap[filePath] = music;
			effect._music = music;

		}
		else
		{
			effect._music = it->second;
		}
		return effect;
	}

}