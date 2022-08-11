#include "MainCharacter.hpp"
#include <iostream>

MainCharacter::MainCharacter(sf::RenderWindow &window, float x, float y)
    : GameObj(window, x, y), mAnimationIndex(0), mFrameIndex(0)
{
    if (!mTexture.loadFromFile("data/cat.png"))
    {
        std::cout << "failed to load from file" << std::endl;
        exit(1);
    }

    int frameW = mTexture.getSize().x / 4;
    int frameH = mTexture.getSize().y / 4;

    mSprites.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mSprites[i].push_back(make_unique<sf::Sprite>(mTexture, sf::IntRect(j * frameW, i * frameH, frameW, frameH)));
            mSprites[i].back()->setScale(6, 6);
        }
    }
}

void MainCharacter::draw()
{
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mCoords);
    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f, mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (curState == State::goLeft || curState == State::goRight || curState == State::goUp || curState == State::goDown)
    {
        ++mCounter;
        if (mCounter == 20)
        {
            mCounter = 0;
            mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
        }
    }
}
void MainCharacter::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && curState != State::goLeft)
    {
        curState = State::goLeft;
        mAnimationIndex = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && curState != State::goRight)
    {
        curState = State::goRight;
        mAnimationIndex = 2;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && curState != State::goUp)
    {
        curState = State::goUp;
        mAnimationIndex = 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && curState != State::goDown)
    {
        curState = State::goDown;
        mAnimationIndex = 0;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
             !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        mFrameIndex = 0;
        if (curState == State::goLeft)
        {
            curState = State::standLeft;
        }
        else if (curState == State::goRight)
        {
            curState = State::standRight;
        }
        else if (curState == State::goUp)
        {
            curState = State::standUp;
        }
        else if (curState == State::goDown)
        {
            curState = State::standDown;
        }
    }
}
