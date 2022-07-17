#include "Ball.hpp"
#include "..\libs\random.hpp"

using namespace std;
using Random = effolkronium::random_static;

Ball::Ball(sf::RenderWindow &window, Block &block, Player &player)
    : mWindow(window), mBlock(block), mPlayer(player)
{
    mBall.setRadius(10);
    mBall.setOrigin(mBall.getRadius(), mBall.getRadius());
    mBall.setFillColor(sf::Color::Yellow);
    mBall.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 300));

    float SpeedValue = std::min(mWindow.getSize().x, mWindow.getSize().y);
    float angle = Random::get(0.0f, 2 * 3.1415f);
    mSpeed = sf::Vector2f(SpeedValue * cos(angle), SpeedValue * sin(angle));
}

sf::Vector2f Ball::getPos()
{
    return mBall.getPosition();
}

void Ball::draw()
{
    mWindow.draw(mBall);
}

void Ball::move(float time)
{
    sf::Vector2f curPos = mBall.getPosition();
    sf::Vector2f newPos = curPos + mSpeed * time;

    if (mBlock.getState() >= 0)
    {
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
    }

    if (mPlayer.isBelow(curPos.x, curPos.y) && mPlayer.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = (mPlayer.getPos().y + mPlayer.getSize().y + mBall.getRadius()) - newPos.y;
        newPos.y = (mPlayer.getPos().y + mPlayer.getSize().y + mBall.getRadius()) + excess;
        mSpeed.y = -mSpeed.y;
    }
    else if (mPlayer.isAbove(curPos.x, curPos.y) && mPlayer.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = newPos.y - (mPlayer.getPos().y - mBall.getRadius());
        newPos.y = (mPlayer.getPos().y - mBall.getRadius()) - excess;
        mSpeed.y = -mSpeed.y;
    }
    else if (mPlayer.isLeft(curPos.x, curPos.y) && mPlayer.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = newPos.x - (mPlayer.getPos().x - mBall.getRadius());
        newPos.x = (mPlayer.getPos().x - mBall.getRadius()) - excess;
        mSpeed.x = -mSpeed.x;
    }
    else if (mPlayer.isRight(curPos.x, curPos.y) && mPlayer.inRect(newPos.x, newPos.y, mBall.getRadius()))
    {
        float excess = (mPlayer.getPos().x + mPlayer.getSize().x + mBall.getRadius()) - newPos.x;
        newPos.x = (mPlayer.getPos().x + mPlayer.getSize().x + mBall.getRadius()) + excess;
        mSpeed.x = -mSpeed.x;
    }
    else if (mPlayer.inRect(newPos.x, newPos.y, mBall.getRadius()))
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
