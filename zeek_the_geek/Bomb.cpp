#include "Game.hpp"

Game::Bomb::Bomb(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c), mActivated(false)

{
}

void Game::Bomb::draw()
{
    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f,
                                                      mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (curState == State::Moving || mActivated)
    {
        ++mCounter;
        if (--mCounterExp == 0)
        {
            mAnimationIndex = 1;
            mFrameIndex = 0;
        }
        cout << mCounterExp << endl;

        if (mCounter == MaxCount)
        {
            if (mFrameIndex == 1 && mCounterExp < 0)
            {
                mGame.mCurMap[mRow][mCol] = '.';
                if (mGame.mCurMap[mRow][mCol - 1] != '.' && mGame.mCurMap[mRow][mCol - 1] != 'W')
                {
                    mGame.mGameObjects[mRow][mCol - 1].release();
                }
                mGame.mGameObjects[mRow][mCol].release();
                return;
            }
            else
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
            }
        }
    }
    move();
}

void Game::Bomb::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    mGame.mGameObjects[mRow + dr][mCol + dc].swap(mGame.mGameObjects[mRow][mCol]);
    swap(mGame.mCurMap[mRow + dr][mCol + dc], mGame.mCurMap[mRow][mCol]);

    mDirection.x = distOfStep * dc;
    mDirection.y = distOfStep * dr;
    mRow += dr;
    mCol += dc;
    curState = State::Moving;
    mActivated = true;
    mCounterExp = 200;
}

bool Game::Bomb::move()
{
    if (curState == State::Moving)
    {
        mX += mDirection.x;
        mY += mDirection.y;
        --mNumOfSteps;
        if (mNumOfSteps == 0)
        {
            mDirection.x = 0;
            mDirection.y = 0;
            curState = State::Standing;
        }
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    }
    return true;
}