#include "Player.h"
#include "Apple.h"
#include "Rock.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		player.position.x = (float)SCREEN_WIDTH / 2.f;
		player.position.y = (float)SCREEN_HEIGHT / 2.f;
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		player.sprite.setTexture(texture);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void UpdatePlayer(Player& player, float timeDelta)
	{
		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.position.y -= player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Right:
		{
			player.position.x += player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.speed * timeDelta;
			break;
		}
		}
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		sf::Vector2f spriteScale = GetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);

		player.sprite.setRotation(0.f);
		player.sprite.setScale(1.f, 1.f);


		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(player.sprite);
	}

	bool HasPlayerCollisionWithScreenBorder(const Player& player)
	{
		return (player.position.x - PLAYER_SIZE / 2.f < 0) ||
			(player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH) ||
			(player.position.y - PLAYER_SIZE / 2.f < 0) ||
			(player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT);
	}

	bool HasPlayerCollisionWithApple(const Player& player, const Apple& apple)
	{
		float dx = player.position.x - apple.position.x;
		float dy = player.position.y - apple.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance <= (PLAYER_SIZE + APPLE_SIZE) / 2.f;
	}

	bool HasPlayerCollisionWithRock(const Player& player, const Rock& rock)
	{
		float dx = player.position.x - rock.position.x;
		float dy = player.position.y - rock.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance <= (PLAYER_SIZE + ROCK_SIZE) / 2.f;
	}
}