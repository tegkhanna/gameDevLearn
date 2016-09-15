//THE AUDIO ENGINE

#pragma once
#include<SDL\SDL_mixer.h>
#include<string>
#include<map>
namespace bengine
{
	class SoundEffect
	{
	public:
		friend class Sounds;
		void play(int loops = 0);
	private:

		Mix_Chunk *_chunk = nullptr;

	};


	class Music
	{
	public:
		friend class Sounds;
		void play(int loops = -1);

		static void pause();
		static void resume();
		static void stop();

	private:

		Mix_Music *_music = nullptr;

	};


	class Sounds
	{
	public:
		Sounds();
		~Sounds();

		void init();//initate
		void destroy();


		void play(); //play

		SoundEffect loadSoundEffect(const std::string &filePath); // it works like texture cahce like the mapping
		Music loadMusic(const std::string &filePath); // it works like texture cahce like the mapping

	private:
		
		std::map<std::string, Mix_Chunk*> _effectMap;
		std::map<std::string, Mix_Music*> _musicMap;

		bool _isInitialised = false;

	};

}