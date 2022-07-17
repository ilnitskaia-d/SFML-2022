#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Player.hpp"

class Ball
{
    sf::RenderWindow &mWindow;
    sf::CircleShape mBall;
    Block &mBlock;
    Player &mPlayer;
    sf::Vector2f mSpeed;

public:
    Ball(sf::RenderWindow &window, Block &block, Player &player);
    sf::Vector2f getPos();
    void draw();
    void move(float time);
};