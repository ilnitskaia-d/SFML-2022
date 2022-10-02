#include "Game.hpp"

Game::Snake::Snake(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c), mActivated(false)

{
    mSprites.resize(3);
    sf::Texture text;

    if (!text.loadFromFile("data/snake_left.png"))
    {
        cout << "catn load left" << endl;
    }
    mTextures.push_back(make_unique<sf::Texture>(text));
    mSprites[1].push_back(make_unique<sf::Sprite>(*mTextures.back()));

    if (!text.loadFromFile("data/snake_up.png"))
    {
        cout << "catn load up" << endl;
    }
    mTextures.push_back(make_unique<sf::Texture>(text));
    mSprites[1].push_back(make_unique<sf::Sprite>(*mTextures.back()));

    if (!text.loadFromFile("data/snake_right.png"))
    {
        cout << "catn load right" << endl;
    }
    mTextures.push_back(make_unique<sf::Texture>(text));
    mSprites[1].push_back(make_unique<sf::Sprite>(*mTextures.back()));

    if (!text.loadFromFile("data/snake_down.png"))
    {
        cout << "catn load down" << endl;
    }
    mTextures.push_back(make_unique<sf::Texture>(text));
    mSprites[1].push_back(make_unique<sf::Sprite>(*mTextures.back()));

    if (!text.loadFromFile("data/snake_sleep.png"))
    {
        cout << "cant load snake sleep" << endl;
    }

    mTextures.push_back(make_unique<sf::Texture>(text));
    int frameSize = 32;
    int nFramesX = mTextures.back()->getSize().x / frameSize;
    for (int j = 0; j < nFramesX; ++j)
    {
        mSprites[2].push_back(make_unique<sf::Sprite>(*mTextures.back(), sf::IntRect(j * frameSize, 0, frameSize, frameSize)));
        mSprites[2].back()->setScale(mGame.mScale, mGame.mScale);
    }
}

void Game::Snake::draw()
{
    float originX;
    float originY;
    if (mAnimationIndex == 0 || mAnimationIndex == 2)
    {
        originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f;
        originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f;
    }
    else
    {
        if (mFrameIndex == 0)
        {
            originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width - mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
        else if (mFrameIndex == 1)
        {
            originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height - mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
        else if (mFrameIndex == 2)
        {
            originX = mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
        else if (mFrameIndex == 3)
        {
            originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
    }

    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(originX, originY);
    mSprites[mAnimationIndex][mFrameIndex]->setScale(mGame.mScale, mGame.mScale);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (mActivated)
    {
        ++mCounter;

        if (curState == State::Standing)
        {
            if (mCounter == MaxCount)
            {
                mCounter = 0;

                if ((mFrameIndex + 1) < mSprites[mAnimationIndex].size())
                {
                    mFrameIndex += 1;
                }
                else
                {
                    curState = State::Moving;
                    mActivated = false;
                }
            }
        }
        else if (mCounter == MaxCount * 4 && curState == State::Moving)
        {
            mCounter = 0;
            mAnimationIndex = 2;
            mFrameIndex = 0;
            //TODO : mActivated = false;
            curState = State::Sleeping;
        }
        else if (curState == State::Sleeping)
        {
            if (mCounter == MaxCount * 30)
            {
                mCounter = 0;

                if ((mFrameIndex + 1) < mSprites[mAnimationIndex].size())
                {
                    mFrameIndex += 1;
                }
                else
                {
                    curState = State::Standing;
                    mFrameIndex = 0;
                    mAnimationIndex = 0;
                    mActivated = false;
                }
            }
        }
    }
    move();
}

bool Game::Snake::move()
{
    if (curState == State::Standing)
    {
        if (mGame.mCharacter.getRow() == mRow)
        {
            if (mGame.mCharacter.getCol() == mCol - 1 || mGame.mCharacter.getCol() == mCol + 1)
            {
                mActivated = true;
            }
        }
        else if (mGame.mCharacter.getCol() == mCol)
        {
            if (mGame.mCharacter.getRow() == mRow - 1 || mGame.mCharacter.getRow() == mRow + 1)
            {
                mActivated = true;
            }
        }
    }
    else
    {
        if (!mGame.mCharacter.isCaught())
        {
            if (mGame.mCharacter.getRow() == mRow)
            {
                if (mGame.mCharacter.getCol() == mCol - 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 0;
                    mActivated = true;
                    mGame.mCharacter.setCaught(true);
                }
                else if (mGame.mCharacter.getCol() == mCol + 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 2;
                    mActivated = true;
                    mGame.mCharacter.setCaught(true);
                }
            }
            else if (mGame.mCharacter.getCol() == mCol)
            {
                if (mGame.mCharacter.getRow() == mRow - 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 1;
                    mActivated = true;
                    mGame.mCharacter.setCaught(true);
                }
                else if (mGame.mCharacter.getRow() == mRow + 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 3;
                    mActivated = true;
                    mGame.mCharacter.setCaught(true);
                }
            }
        }
    }
    return true;
}
