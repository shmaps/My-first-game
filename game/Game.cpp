#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	void RestartGame(Game& game)
	{
		int newNumApples = 0; 

		if (game.gameMode & MODE_20_APPLES)
		{
			newNumApples = 20;
		}
		else if (game.gameMode & MODE_50_APPLES)
		{
			newNumApples = 50;
		}
		else
		{
			newNumApples = rand() % MAX_APPLES + 1;
		}

		if (game.currentNumApples != newNumApples)
		{
			if (game.apples != nullptr)
			{
				delete[] game.apples;
				game.apples = nullptr;
			}

			game.currentNumApples = newNumApples;
			game.apples = new Apple[game.currentNumApples];
		}

		InitPlayer(game.player, game.playerTexture);

		for (int i = 0; i < game.currentNumApples; i++)
		{
			InitApple(game.apples[i], game.appleTexture);
		}

		for (int i = 0; i < NUM_ROCKS; i++)
		{
			InitRock(game.rocks[i], game.rockTexture);
		}

		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0;
	}

	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

		//Load sounds
		assert(game.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(game.deathSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		game.eatSound.setBuffer(game.eatSoundBuffer);
		game.deathSound.setBuffer(game.deathSoundBuffer);

		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		game.apples = nullptr;
		game.currentNumApples = 0;

		RestartGame(game);
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (!game.isGameFinished)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				game.player.direction = PlayerDirection::Right;

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				game.player.direction = PlayerDirection::Up;

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				game.player.direction = PlayerDirection::Left;

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				game.player.direction = PlayerDirection::Down;

			UpdatePlayer(game.player, deltaTime);

			// Check mods
			bool hasAcceleration = (game.gameMode & MODE_ACCELERATION) != 0;
			bool isInfinite = (game.gameMode & MODE_INFINITE_APPLES) != 0;

			for (int i = 0; i < game.currentNumApples; ++i)
			{
				if (HasPlayerCollisionWithApple(game.player, game.apples[i]))
				{
					if (isInfinite)
					{
						ResetApplePosition(game.apples[i]);
					}

					else
					{
						game.apples[i] = game.apples[game.currentNumApples - 1];
						game.currentNumApples--;
						i--;
					}

					game.numEatenApples++;

					if (hasAcceleration)
					{
						game.player.speed += ACCELERATION;
					}

					game.eatSound.play();
				}
			}


			if (!isInfinite && game.currentNumApples == 0)
			{
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;
				game.deathSound.play();
			}


			for (int i = 0; i < NUM_ROCKS; ++i)
			{
				if (HasPlayerCollisionWithRock(game.player, game.rocks[i]))
				{
					game.isGameFinished = true;
					game.timeSinceGameFinish = 0.f;

					game.deathSound.play();
				}
			}


			if (HasPlayerCollisionWithScreenBorder(game.player))
			{
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;

				game.deathSound.play();
			}
		}
		else
		{
			if (game.timeSinceGameFinish <= PAUSE_LENGTH)
			{
				game.timeSinceGameFinish += deltaTime;
				game.background.setFillColor(sf::Color::Red);
			}

			else
			{
				game.background.setFillColor(sf::Color::Black);
				RestartGame(game);
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background);

		DrawPlayer(game.player, window);

		for (int i = 0; i < game.currentNumApples; ++i)
			DrawApple(game.apples[i], window);

		for (int i = 0; i < NUM_ROCKS; ++i)
			DrawRock(game.rocks[i], window);
	}

	void DeinitializeGame(Game& game)
	{
		game.eatSound.stop();
		game.deathSound.stop();

		if (game.apples != nullptr)
		{
			delete[] game.apples; 
			game.apples = nullptr;
			game.currentNumApples = 0;
		}
	}
}