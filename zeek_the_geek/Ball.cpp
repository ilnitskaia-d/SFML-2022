#include "Game.hpp"

Game::Ball::Ball(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Ball::draw()
{
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    move();
}

void Game::Ball::startMove(int dr, int dc)
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

bool Game::Ball::move()
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