#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    sf::RenderWindow &mWindow;
    int mX;
    int mY;
    sf::CircleShape mBall;
    sf::Vector2f mSpeed;

public:
    Ball(sf::RenderWindow &window);
    void setRandomSpeed(int r, int R, int dir1, int dir2);
    void draw();
};