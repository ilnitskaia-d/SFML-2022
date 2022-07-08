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
    setRandomSpeed(mBall.getRadius() / 2, mBall.getRadius(), 0, 2 * 3.1415926);
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

void Ball::draw()
{

    if (mBall.getPosition().x + mSpeed.x + mBall.getRadius() >= mWindow.getSize().x)
    {
        mSpeed.x = -mSpeed.x;
    }
    else if (mBall.getPosition().x + mSpeed.x - mBall.getRadius() < 0)
    {
        mSpeed.x = -mSpeed.x;
    }
    else if (mBall.getPosition().y + mSpeed.y + mBall.getRadius() >= mWindow.getSize().y)
    {
        //     float ty = mBall.getPosition().y + mSpeed.y - mWindow.getSize().y;
        //     float tx = ty * mSpeed.x / mSpeed.y;
        //     mBall.setPosition(sf::Vector2f(mBall.getPosition().x + tx, mWindow.getSize().y - 1));
        mSpeed.y = -mSpeed.y;
    }
    else if (mBall.getPosition().y + mSpeed.y - mBall.getRadius() < 0)
    {
        mSpeed.y = -mSpeed.y;
    }

    mBall.setPosition(mBall.getPosition() + mSpeed);
    mWindow.draw(mBall);
}