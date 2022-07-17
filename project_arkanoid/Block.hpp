#pragma once
#include <SFML/Graphics.hpp>

class Block
{
    sf::RenderWindow &mWindow;
    sf::RectangleShape mBlock;
    int curState;

public:
    Block(sf::RenderWindow &window);
    bool isBelow(float x, float y) const;
    bool isAbove(float x, float y) const;
    bool isLeft(float x, float y) const;
    bool isRight(float x, float y) const;
    bool inRect(float x, float y, float r);
    sf::Vector2f getSize();
    sf::Vector2f getPos();
    int getState() const;
    void draw() const;
};