#include "Ball.hpp"
#include "..\libs\random.hpp"
#include <memory>

using namespace std;
using Random = effolkronium::random_static;

Ball::Ball(sf::RenderWindow &window, vector<unique_ptr<Block>> &blocks, Player &player)
    : mWindow(window), mBlocks(blocks), mPlayer(player)
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

    for (auto &block : mBlocks)
    {
        if (block->getState() >= 0)
        {
            if (block->isBelow(curPos.x, curPos.y) && block->inRect(newPos.x, newPos.y, mBall.getRadius()))
            {
                float excess = (block->getPos().y + block->getSize().y + mBall.getRadius()) - newPos.y;
                newPos.y = (block->getPos().y + block->getSize().y + mBall.getRadius()) + excess;
                mSpeed.y = -mSpeed.y;
            }
            else if (block->isAbove(curPos.x, curPos.y) && block->inRect(newPos.x, newPos.y, mBall.getRadius()))
            {
                float excess = newPos.y - (block->getPos().y - mBall.getRadius());
                newPos.y = (block->getPos().y - mBall.getRadius()) - excess;
                mSpeed.y = -mSpeed.y;
            }
            else if (block->isLeft(curPos.x, curPos.y) && block->inRect(newPos.x, newPos.y, mBall.getRadius()))
            {
                float excess = newPos.x - (block->getPos().x - mBall.getRadius());
                newPos.x = (block->getPos().x - mBall.getRadius()) - excess;
                mSpeed.x = -mSpeed.x;
            }
            else if (block->isRight(curPos.x, curPos.y) && block->inRect(newPos.x, newPos.y, mBall.getRadius()))
            {
                float excess = (block->getPos().x + block->getSize().x + mBall.getRadius()) - newPos.x;
                newPos.x = (block->getPos().x + block->getSize().x + mBall.getRadius()) + excess;
                mSpeed.x = -mSpeed.x;
            }
            else if (block->inRect(newPos.x, newPos.y, mBall.getRadius()))
            {
                mSpeed.x = -mSpeed.x + Random::get(-1, 1);
                mSpeed.y = -mSpeed.y + Random::get(-1, 1);
            }
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
