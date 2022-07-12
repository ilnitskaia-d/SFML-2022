#include "Block.hpp"

Block::Block(sf::RenderWindow &window)
    : mWindow(window)
{
    mBlock.setSize(sf::Vector2f(100, 100));
    mBlock.setFillColor(sf::Color::White);
    mBlock.setPosition(sf::Vector2f(mWindow.getSize().x / 2 - mBlock.getSize().x / 2, mWindow.getSize().y / 2 - mBlock.getSize().y));
}

bool Block::isBelow(float x, float y) const
{
    return mBlock.getPosition().y + mBlock.getSize().y < y &&
           mBlock.getPosition().x < x && x < mBlock.getPosition().x + mBlock.getSize().x;
}

bool Block::isAbove(float x, float y) const
{
    return mBlock.getPosition().y > y &&
           mBlock.getPosition().x < x && x < mBlock.getPosition().x + mBlock.getSize().x;
}

bool Block::isLeft(float x, float y) const
{
    return mBlock.getPosition().x > x &&
           mBlock.getPosition().y < y && y < mBlock.getPosition().y + mBlock.getSize().y;
}

bool Block::isRight(float x, float y) const
{
    return mBlock.getPosition().x + mBlock.getSize().x < x &&
           mBlock.getPosition().y < y && y < mBlock.getPosition().y + mBlock.getSize().y;
}

bool Block::isLeftBelow(float x, float y) const
{
    return mBlock.getPosition().x + mBlock.getSize().x > x &&
           mBlock.getPosition().y < y;
}



bool Block::inRect(float x, float y, float r)
{
    return mBlock.getPosition().x - r < x && x < mBlock.getPosition().x + mBlock.getSize().x + r &&
           mBlock.getPosition().y - r < y && y < mBlock.getPosition().y + mBlock.getSize().y + r;
}

sf::Vector2f Block::getSize()
{
    return mBlock.getSize();
}
sf::Vector2f Block::getPos()
{
    return mBlock.getPosition();
}

void Block::draw() const
{
    mWindow.draw(mBlock);
}