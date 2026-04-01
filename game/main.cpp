#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
#include <iostream>


int main()
{
	using namespace ApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);

	std::cout << "Choose Game Mode" << std::endl;
	std::cout << "1. 20 apples + acceleration + infinite_apples" << std::endl;
	std::cout << "2. 20 apples + no_acceleration + infinite_apples" << std::endl;
	std::cout << "3. 50 apples + acceleration + infinite_apples" << std::endl;
	std::cout << "4. 20 apples + acceleration + ending_apples" << std::endl;
	std::cout << "5. 20 apples + no_acceleration + ending_apples" << std::endl;
	std::cout << "6. 50 apples + acceleration + ending_apples" << std::endl;
	std::cout << "7. Random mode (apples from 1 to 50)" << std::endl;
	std::cout << "Select mode (1-7):";

	int modeChoice;
	std::cin >> modeChoice;

	// Checking correct num of modes
	while (modeChoice < 1 || modeChoice > 7)
	{
		std::cout << "Wrong choice! Only from 1 to 7:";
		std::cin >> modeChoice;
	}

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	Game game;
	
	// Set Mode
	switch (modeChoice)
	{
	case 1:
		game.gameMode = MODE_20_APPLES | MODE_ACCELERATION | MODE_INFINITE_APPLES;
		break;

	case 2:
		game.gameMode = MODE_20_APPLES | MODE_INFINITE_APPLES;
		break;

	case 3:
		game.gameMode = MODE_50_APPLES | MODE_ACCELERATION | MODE_INFINITE_APPLES;
		break;

	case 4:
		game.gameMode = MODE_20_APPLES | MODE_ACCELERATION;
		break;

	case 5:
		game.gameMode = MODE_20_APPLES;
		break;

	case 6:
		game.gameMode = MODE_50_APPLES | MODE_ACCELERATION;
		break;

	case 7:
		game.gameMode = 0;
		break;
	}

	InitGame(game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		sf::sleep(sf::milliseconds(16));

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
		}

		UpdateGame(game, deltaTime);

		// Draw game
		window.clear();
		DrawGame(game, window);

		window.display();
	}

	// Deinitialization
	DeinitializeGame(game);

	return 0;
}