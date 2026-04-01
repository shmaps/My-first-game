#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "SFML/Audio.hpp"

namespace ApplesGame
{
	struct Game
	{
		Player player;
		Apple* apples = nullptr;
		int currentNumApples = 0;
		int maxApples = MAX_APPLES;
		Rock rocks[NUM_ROCKS];

		int gameMode;

		// Global game data
		int numEatenApples = 0;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		sf::RectangleShape background;

		//Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		//Sound
		sf::SoundBuffer eatSoundBuffer;
		sf::SoundBuffer deathSoundBuffer;
		sf::Sound eatSound;
		sf::Sound deathSound;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinitializeGame(Game& game);
}
