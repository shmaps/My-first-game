#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    struct Apple;
    struct Rock;

    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D position;
        float speed = 0.f;
        PlayerDirection direction = PlayerDirection::Right;
        sf::Sprite sprite;
    };

    void InitPlayer(Player& player, const sf::Texture& texture);
    void UpdatePlayer(Player& player, float deltaTime);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
   
    bool HasPlayerCollisionWithScreenBorder(const Player& player);
    bool HasPlayerCollisionWithApple(const Player& player, const Apple& apple);
    bool HasPlayerCollisionWithRock(const Player& player, const Rock& rock);
}