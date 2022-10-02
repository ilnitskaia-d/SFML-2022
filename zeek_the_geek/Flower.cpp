#include "Game.hpp"

Game::Flower::Flower(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Flower::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Flower::activate()
{
    mGame.mCurMap[mRow][mCol] = '.';
    mGame.mGameObjects[mRow][mCol].release();
    mActivated = true;
    mGame.mScore++;
}
