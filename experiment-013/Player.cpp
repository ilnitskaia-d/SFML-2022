#include "Player.hpp"
#include <iostream>
using namespace std;

Player::Player(sf::RenderWindow &window)
    : mWindow(window), mX(window.getSize().x / 2), mY(window.getSize().y - 30)
{
    mPlatform.setSize(sf::Vector2f(300, 10));
    mPlatform.setOrigin(sf::Vector2f(mPlatform.getSize().x / 2, mPlatform.getSize().y / 2));
    mPlatform.setFillColor(sf::Color::White);
    mPlatform.setPosition(sf::Vector2f(mX, mY));
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
