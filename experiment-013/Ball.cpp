#include "Ball.hpp"
#include "..\libs\random.hpp"

using namespace std;
using Random = effolkronium::random_static;

Ball::Ball(sf::RenderWindow &window)
    : mWindow(window), mX(window.getSize().x / 2), mY(window.getSize().y / 2)
{
    mBall.setRadius(30);
    mBall.setOrigin(mBall.getRadius(), mBall.getRadius());
    mBall.setFillColor(sf::Color::White);
    mBall.setPosition(sf::Vector2f(mX, mY));

    float SpeedValue = std::min(mWindow.getSize().x, mWindow.getSize().y);
    float angle = Random::get(0.0f, 2 * 3.1415f);
    sf::Vector2f speed(SpeedValue * cos(angle), SpeedValue * sin(angle));
}

void Ball::setRandomSpeed(int r, int R, int dir1, int dir2)
{
    float i = Random::get(r, R);
    // float i = 1;
    float j = Random::get(dir1, dir2);
    float dx = i * cos(j);
    float dy = j * sin(j);
    mSpeed = sf::Vector2f(dx, dy);
}

void Ball::draw(sf::Time TimePerFrame)
{
    if (mBall.getPosition().y > mWindow.getSize().y - mBall.getRadius())
    {
        float excess = mBall.getPosition().y - (mWindow.getSize().y - mBall.getRadius());
        mBall.setPosition(mBall.getPosition().x, mWindow.getSize().y - mBall.getRadius() - excess);
        mSpeed.y = -mSpeed.y;
    }
    else if (mBall.getPosition().y < mBall.getRadius())
    {
        float excess = mBall.getRadius() - mBall.getPosition().y;
        mBall.setPosition(mBall.getPosition().x, mBall.getRadius() + excess);
        mSpeed.y = -mSpeed.y;
    }
    else if (mBall.getPosition().x > mWindow.getSize().x - mBall.getRadius())
    {
        float excess = mBall.getPosition().x - (mWindow.getSize().x - mBall.getRadius());
        mBall.setPosition(mWindow.getSize().x - mBall.getRadius() - excess, mBall.getPosition().y);
        mSpeed.x = -mSpeed.x;
    }
    else if (mBall.getPosition().x < mBall.getRadius())
    {
        float excess = mBall.getRadius() - mBall.getPosition().x;
        mBall.setPosition(mBall.getRadius() + excess, mBall.getPosition().y);
        mSpeed.x = -mSpeed.x;
    }

    mBall.setPosition(mBall.getPosition() + mSpeed);
    mBall.move(mSpeed * TimePerFrame.asSeconds());
    mWindow.draw(mBall);
}