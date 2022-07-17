#include "Player.hpp"
#include <iostream>
using namespace std;

Player::Player(sf::RenderWindow &window)
    : mWindow(window)
{
    mPlatform.setSize(sf::Vector2f(300, 30));
    mPlatform.setOrigin(sf::Vector2f(mPlatform.getSize().x / 2, mPlatform.getSize().y / 2));
    mPlatform.setFillColor(sf::Color::White);
    mPlatform.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 30));
}

sf::Vector2f Player::getSize()
{
    return mPlatform.getSize();
}

sf::Vector2f Player::getPos()
{
    return mPlatform.getPosition() - (mPlatform.getSize() / 2.0f);
}

void Player::draw()
{
    mWindow.draw(mPlatform);
}

void Player::move()
{
    int coordsX = sf::Mouse::getPosition(mWindow).x;
    if (coordsX + mPlatform.getSize().x / 2 < mWindow.getSize().x && coordsX - mPlatform.getSize().x / 2 > 0)
    {
        mPlatform.setPosition(sf::Vector2f(coordsX, mPlatform.getPosition().y));
    }
}

bool Player::isBelow(float x, float y) const
{
    return mPlatform.getPosition().y + mPlatform.getSize().y / 2 < y &&
           mPlatform.getPosition().x - mPlatform.getSize().x / 2 < x &&
           x < mPlatform.getPosition().x + mPlatform.getSize().x / 2;
}

bool Player::isAbove(float x, float y) const
{
    return mPlatform.getPosition().y - mPlatform.getSize().y / 2 > y &&
           mPlatform.getPosition().x - mPlatform.getSize().x / 2 < x &&
           x < mPlatform.getPosition().x + mPlatform.getSize().x / 2;
}

bool Player::isLeft(float x, float y) const
{
    return mPlatform.getPosition().x - mPlatform.getSize().x / 2 > x &&
           mPlatform.getPosition().y - mPlatform.getSize().y / 2 < y &&
           y < mPlatform.getPosition().y + mPlatform.getSize().y / 2;
}

bool Player::isRight(float x, float y) const
{
    return mPlatform.getPosition().x + mPlatform.getSize().x / 2 < x &&
           mPlatform.getPosition().y - mPlatform.getSize().y / 2 < y &&
           y < mPlatform.getPosition().y + mPlatform.getSize().y / 2;
}

bool Player::inRect(float x, float y, float r)
{
    return mPlatform.getPosition().x - mPlatform.getSize().x / 2 - r < x &&
           x < mPlatform.getPosition().x + mPlatform.getSize().x / 2 + r &&
           mPlatform.getPosition().y - mPlatform.getSize().y / 2 - r < y &&
           y < mPlatform.getPosition().y + mPlatform.getSize().y / 2 + r;
}
