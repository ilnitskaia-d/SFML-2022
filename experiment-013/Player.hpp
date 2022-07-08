#pragma once
#include <SFML/Graphics.hpp>

class Player
{
    sf::RenderWindow &mWindow;
    int mX;
    int mY;
    sf::RectangleShape mPlatform;

public:
    Player(sf::RenderWindow &window);
    void draw();
    void move();
};