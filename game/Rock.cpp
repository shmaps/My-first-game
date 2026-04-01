#include "Rock.h"

namespace ApplesGame
{
	void InitRock(Rock& rock, const sf::Texture& texture)
	{
		rock.sprite.setTexture(texture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);

		rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		window.draw(rock.sprite);
	}
}