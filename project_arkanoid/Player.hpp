#pragma once
#include <SFML/Graphics.hpp>

class Player
{
    sf::RenderWindow &mWindow;
    sf::RectangleShape mPlatform;

public:
    Player(sf::RenderWindow &window);

    void increaseSize(int n);
    void restoreSize(int n);
    sf::Vector2f getSize();
    sf::Vector2f getPos();
    void draw();
    void move();
    bool isBelow(float x, float y) const;
    bool isAbove(float x, float y) const;
    bool isLeft(float x, float y) const;
    bool isRight(float x, float y) const;
    bool inRect(float x, float y, float r);
};