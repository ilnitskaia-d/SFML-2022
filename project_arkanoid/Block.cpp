#include "Block.hpp"

Block::Block(void *game, sf::RenderWindow &window, float x, float y, float w, float h, void magic(void *, void *), void endMagic(void *))
    : mPtrToGame(game), mWindow(window), mCurState(1), mPtrMagic(magic), mPtrEndMagic(endMagic)
{
    mBlock.setSize(sf::Vector2f(w, h));
    mBlock.setOutlineColor(sf::Color::Black);
    mBlock.setOutlineThickness(5);
    mBlock.setFillColor(sf::Color::White);
    mBlock.setPosition(sf::Vector2f(x, y));
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

bool Block::inRect(float x, float y, float r)
{
    if (mBlock.getPosition().x - r < x && x < mBlock.getPosition().x + mBlock.getSize().x + r &&
        mBlock.getPosition().y - r < y && y < mBlock.getPosition().y + mBlock.getSize().y + r)
    {
        mCurState--;
        if (mCurState == -1)
        {
            if (mPtrMagic)
            {
                mPtrMagic(mPtrToGame, reinterpret_cast<void *>(mPtrEndMagic));
            }
        }
        mBlock.setFillColor(sf::Color(100, 100, 100));
        return true;
    }

    return false;
}

sf::Vector2f Block::getSize()
{
    return mBlock.getSize();
}

sf::Vector2f Block::getPos()
{
    return mBlock.getPosition();
}

int Block::getState() const
{
    return mCurState;
}

void Block::draw() const
{
    if (mCurState >= 0)
    {
        mWindow.draw(mBlock);
    }
}