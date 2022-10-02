#include "Game.hpp"

Game::BadCat::BadCat(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c), mActivated(false)

{
}

void Game::BadCat::activate()
{
    if (curState == State::Standing)
    {
        mActivated = true;
        mCounterExp = 100;
    }
}

void Game::BadCat::draw()
{
    if (curState == State::Standing && !mActivated)
    {
        if (mGame.mCurMap[mRow - 1][mCol] == 'R' || mGame.mCurMap[mRow + 1][mCol] == 'R' ||
            mGame.mCurMap[mRow][mCol - 1] == 'R' || mGame.mCurMap[mRow][mCol + 1] == 'R')
        {
            activate();
            if (auto p = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow + 1][mCol].get()))
            {
                p->activate();
            }
            if (auto p1 = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow - 1][mCol].get()))
            {
                p1->activate();
            }
            if (auto p2 = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow][mCol - 1].get()))
            {
                p2->activate();
            }
            if (auto p3 = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow][mCol + 1].get()))
            {
                p3->activate();
            }
        }
    }

    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f,
                                                      mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (mActivated)
    {
        ++mCounter;
        if (--mCounterExp == 0)
        {
            mAnimationIndex = 1;
            mFrameIndex = 0;
        }

        if (mCounter == MaxCount)
        {
            if (mFrameIndex == 1 && mCounterExp < 0)
            {
                mGame.mCurMap[mRow][mCol] = '.';
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

void Game::BadCat::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    dRow = dr;
    dCol = dc;

    mDirection.x = distOfStep * dc;
    mDirection.y = distOfStep * dr;

    curState = State::Moving;
}

bool Game::BadCat::move()
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

            mGame.mGameObjects[mRow + dRow][mCol + dCol].swap(mGame.mGameObjects[mRow][mCol]);
            swap(mGame.mCurMap[mRow + dRow][mCol + dCol], mGame.mCurMap[mRow][mCol]);

            mRow += dRow;
            mCol += dCol;
        }
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    }
    return true;
}
