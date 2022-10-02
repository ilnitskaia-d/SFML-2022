#include "Game.hpp"

Game::MainCharacter::MainCharacter(Game &game)
    : mGame(game),
      mCounter(0), mAnimationIndex(0), mFrameIndex(0), curState(State::Standing), mDirection(sf::Vector2f(0.0f, 0.0f)),
      mHasKey(false), mIsCaught(false)
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
        }
    }
}

void Game::MainCharacter::reset()
{
    mCounter = 0;
    mAnimationIndex = 0;
    mFrameIndex = 0;
    curState = State::Standing;
    mDirection.x = 0;
    mDirection.y = 0;
    mHasKey = false;
    mIsCaught = false;
}

void Game::MainCharacter::setCoords(int row, int col)
{
    mRow = row;
    mCol = col;
    for (auto const &v : mSprites)
    {
        for (auto &p : v)
        {
            p->setScale(mGame.mScale, mGame.mScale);
        }
    }
    float x = mGame.mCenterX + mSprites[0][0]->getGlobalBounds().width * col;
    float y = mGame.mCenterY + mSprites[0][0]->getGlobalBounds().width * row;
    mCoords = sf::Vector2f(x, y);
}

void Game::MainCharacter::draw()
{
    if (!mIsCaught)
    {
        mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f,
                                                          mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mCoords);
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
        if (curState == State::Moving)
        {
            ++mCounter;
            if (mCounter == MaxCount)
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
            }
        }
        move();
    }
}

bool Game::MainCharacter::canMove(int dr, int dc) const
{
    if (mGame.mCurMap[mRow + dr][mCol + dc] == '.')
    {
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'A' &&
        mGame.mCurMap[mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Apple *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'B' &&
        mGame.mCurMap[mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Ball *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'E' &&
        mGame.mCurMap[mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Bomb *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'R' &&
        mGame.mCurMap[mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'F')
    {
        auto p = dynamic_cast<Flower *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'M')
    {
        auto p = dynamic_cast<Mouse *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'K')
    {
        auto p = dynamic_cast<Key *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return true;
    }

    if (mGame.mCurMap[mRow + dr][mCol + dc] == 'D')
    {
        auto p = dynamic_cast<Door *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return p->getActivStatus();
    }

    return false;
}

void Game::MainCharacter::setKey(bool b)
{
    mHasKey = b;
}

bool Game::MainCharacter::getKey()
{
    return mHasKey;
}

void Game::MainCharacter::setCaught(bool b)
{
    mIsCaught = b;
}

bool Game::MainCharacter::isCaught()
{
    return mIsCaught;
}

void Game::MainCharacter::move()
{
    if (curState == State::Moving)
    {
        mCoords += mDirection;
        --mNumOfSteps;
        if (mNumOfSteps == 0)
        {
            curState = State::Standing;
            mFrameIndex = 0;
            mDirection.x = 0;
            mDirection.y = 0;
        }
    }
    else
    {
        mNumOfSteps = MaxCount * 4;
        float distOfStep = mGame.mCellSize / mNumOfSteps;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && canMove(0, -1))
        {
            curState = State::Moving;
            mDirection.x = -distOfStep;
            mDirection.y = 0;
            mAnimationIndex = 1;
            mFrameIndex = 0;
            --mCol;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && canMove(0, 1))
        {
            curState = State::Moving;
            mDirection.x = distOfStep;
            mDirection.y = 0;
            mAnimationIndex = 2;
            mFrameIndex = 0;
            ++mCol;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canMove(-1, 0))
        {
            curState = State::Moving;
            mDirection.x = 0;
            mDirection.y = -distOfStep;
            mAnimationIndex = 3;
            mFrameIndex = 0;
            --mRow;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && canMove(1, 0))
        {
            curState = State::Moving;
            mDirection.x = 0;
            mDirection.y = distOfStep;
            mAnimationIndex = 0;
            mFrameIndex = 0;
            ++mRow;
        }
    }
}