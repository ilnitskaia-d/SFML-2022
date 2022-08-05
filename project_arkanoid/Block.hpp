#pragma once
#include <SFML/Graphics.hpp>

class Block
{
    void *mPtrToGame;
    sf::RenderWindow &mWindow;
    sf::RectangleShape mBlock;
    int mCurState;
    void (*mPtrMagic)(void *, void *);
    void (*mPtrEndMagic)(void *);

public:
    Block(void *ptrToGame, sf::RenderWindow &window, float x, float y, float w, float h, void magic(void *, void *), void endMagic(void *));
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