#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2D { float x = 0, y = 0; };
	typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);
	bool IsRectanglesCollide(Position2D rect1Pos, Vector2D rect1Size,
		Position2D rect2Pos, Vector2D rect2Size);
	bool IsCirclesCollide(Position2D circle1Pos, float r1,
		Position2D circle2Pos, float r2);
	void SetSpriteSize(sf::Sprite& sprite, float width, float height);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float ox, float oy);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, float desiredWidth, float desiredHeight);
}