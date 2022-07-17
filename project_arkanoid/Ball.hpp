#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"

class Ball
{

    sf::RenderWindow &mWindow;
    sf::CircleShape mBall;
    Block &mBlock;
    sf::Vector2f mSpeed;

public:
    Ball(sf::RenderWindow &window, Block &block);
    sf::Vector2f getPos();
    void draw();
    void move(float time);
};