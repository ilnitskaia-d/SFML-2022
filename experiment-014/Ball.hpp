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
    void draw();
    void setPos();
    sf::Vector2f getPos();
    void move(float time);
    void setSpeed(sf::Vector2f v);
};