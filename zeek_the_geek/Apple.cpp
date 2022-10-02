#include "Game.hpp"

Game::Apple::Apple(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Apple::draw()
{
    move();
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
}

void Game::Apple::startMove(int dr, int dc)
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
}

bool Game::Apple::move()
{
    if (curState == State::Moving)
    {
        mX += mDirection.x;
        mY += mDirection.y;
        cout << mX << " " << mY << endl;
        --mNumOfSteps;
        if (mNumOfSteps == 0)
        {
            mDirection.x = 0;
            mDirection.y = 0;
            curState = State::Standing;
        }
        mSprites[mAnimationIndex][mFrameIndex]->move(mDirection);
    }
    return true;
}
