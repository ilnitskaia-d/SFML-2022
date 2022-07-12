#include "Ball.hpp"
#include "..\libs\random.hpp"

using namespace std;
using Random = effolkronium::random_static;

Ball::Ball(sf::RenderWindow &window, Block &block)
    : mWindow(window), mBlock(block)
{
    mBall.setRadius(10);
    mBall.setOrigin(mBall.getRadius(), mBall.getRadius());
    mBall.setFillColor(sf::Color::Yellow);
    mBall.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    // float SpeedValue = std::min(mWindow.getSize().x, mWindow.getSize().y);
    // float angle = Random::get(0.0f, 2 * 3.1415f);
    // sf::Vector2f mSpeed(SpeedValue * cos(angle), SpeedValue * sin(angle));
}

sf::Vector2f Ball::getPos()
{
    return mBall.getPosition();
}

void Ball::setSpeed(sf::Vector2f v)
{
    mSpeed = v;
}

void Ball::draw()
{
    mWindow.draw(mBall);
}

void Ball::setPos()
{
    int coordsX = sf::Mouse::getPosition(mWindow).x;
    int coordsY = sf::Mouse::getPosition(mWindow).y;
    if (coordsX + mBall.getRadius() / 2 < mWindow.getSize().x && coordsX - mBall.getRadius() / 2 > 0 && coordsY + mBall.getRadius() / 2 < mWindow.getSize().y && coordsY - mBall.getRadius() / 2 > 0)
    {
        mBall.setPosition(sf::Vector2f(coordsX, coordsY));
    }
}

void Ball::move(float time)
{
    // mBall.setPosition(mBall.getPosition() + mSpeed * time);

    sf::Vector2f curPos = mBall.getPosition();
    sf::Vector2f newPos = curPos + mSpeed * time;

    if (mBlock.isBelow(curPos.x, curPos.y) && mBlock.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = (mBlock.getPos().y + mBlock.getSize().y + mBall.getRadius()) - newPos.y;
        newPos.y = (mBlock.getPos().y + mBlock.getSize().y + mBall.getRadius()) + excess;
        mSpeed.y = -mSpeed.y;
    }
    else if (mBlock.isAbove(curPos.x, curPos.y) && mBlock.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = newPos.y - (mBlock.getPos().y - mBall.getRadius());
        newPos.y = (mBlock.getPos().y - mBall.getRadius()) - excess;
        mSpeed.y = -mSpeed.y;
    }
    else if (mBlock.isLeft(curPos.x, curPos.y) && mBlock.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = newPos.x - (mBlock.getPos().x - mBall.getRadius());
        newPos.x = (mBlock.getPos().x - mBall.getRadius()) - excess;
        mSpeed.x = -mSpeed.x;
    }
    else if (mBlock.isRight(curPos.x, curPos.y) && mBlock.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = (mBlock.getPos().x + mBlock.getSize().x + mBall.getRadius()) - newPos.x;
        newPos.x = (mBlock.getPos().x + mBlock.getSize().x + mBall.getRadius()) + excess;
        mSpeed.x = -mSpeed.x;
    }
    else if (mBlock.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        mSpeed.x = -mSpeed.x + Random::get(-1, 1);
        mSpeed.y = -mSpeed.y + Random::get(-1, 1);
    }

    mBall.setPosition(newPos);

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
}
