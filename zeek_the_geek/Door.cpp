#include "Game.hpp"

Game::Door::Door(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Door::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Door::activate()
{
    if (mGame.mCharacter.getKey())
    {
        mGame.mCurMap[mRow][mCol] = '.';
        // mGame.mGameObjects[mRow][mCol].release();
        mGame.mCharacter.setKey(false);
        mActivated = true;
    }
}

Game::Key::Key(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Key::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Key::activate()
{
    mGame.mCurMap[mRow][mCol] = '.';
    mGame.mCharacter.setKey(true);
    mActivated = true;
}
