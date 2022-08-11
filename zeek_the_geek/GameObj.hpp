#pragma once
#include <SFML/Graphics.hpp>

class GameObj
{
protected:
    sf::RenderWindow &mWindow;
    sf::Vector2f mCoords;
    sf::Texture mTexture;

public:
    GameObj(sf::RenderWindow &window, float x, float y)
        : mWindow(window), mCoords(sf::Vector2f(x, y))
    {
    }

    virtual void draw() = 0;
};