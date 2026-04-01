#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f; // Pixels per second
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 20.f; // Pixels per second
	const int MAX_APPLES = 50;
	const float APPLE_SIZE = 20.f;
	const float PAUSE_LENGTH = 3.f;
	const int NUM_ROCKS = 10;
	const float ROCK_SIZE = 30.f;

	const std::string EAT_SOUND_PATH = RESOURCES_PATH + "AppleEat";
	const std::string DEATH_SOUND_PATH = RESOURCES_PATH + "Death";


	const int MODE_20_APPLES = 1;        // 1 = 20 apples
	const int MODE_50_APPLES = 2;        // 2 = 50 apples
	const int MODE_ACCELERATION = 4;     // 4 = acceleration
	const int MODE_INFINITE_APPLES = 8;  // 8 = Infinite apples
}