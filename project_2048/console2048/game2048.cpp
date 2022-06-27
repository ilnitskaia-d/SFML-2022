#include "game2048.hpp"
#include "..\..\libs\random.hpp"
#include <iostream>

using namespace std;
using Random = effolkronium::random_static;

Game2048::Game2048(int goal)
    : mPuzzle(4, vector<int>(4)), mGoal(goal), mCurrScore(0), mWin(false)
{
    addRandomNums();
    addRandomNums();
}

void Game2048::addRandomNums()
{
    vector<pair<int, int>> freeTiles;
    for (size_t i = 0; i < mPuzzle.size(); i++)
    {
        for (size_t j = 0; j < mPuzzle[i].size(); j++)
        {
            if (mPuzzle[i][j] == 0)
            {
                freeTiles.emplace_back(i, j);
            }
        }
    }

    int size = freeTiles.size() - 1;
    int tile = Random::get(0, size);
    int prob = Random::get(1, 10);

    if (prob < 3)
    {
        mPuzzle[freeTiles[tile].first][freeTiles[tile].second] = 4;
    }
    else
    {
        mPuzzle[freeTiles[tile].first][freeTiles[tile].second] = 2;
    }
}

int Game2048::getAt(int r, int c) const
{
    return mPuzzle[r][c];
}

bool Game2048::getWinStatus() const
{
    return mWin;
}

int Game2048::getCurrScore() const
{
    return mCurrScore;
}

bool Game2048::canMove()
{
    for (int i = 0; i < mPuzzle.size(); i++)
    {
        for (int j = 0; j < mPuzzle[i].size(); j++)
        {
            int curNum = mPuzzle[i][j];
            if (curNum == 0)
            {
                return true;
            }

            if ((j + 1 < mPuzzle.size() && (curNum == mPuzzle[i][j + 1] || mPuzzle[i][j + 1] == 0)) || (j - 1 >= 0 && (curNum == mPuzzle[i][j - 1] || mPuzzle[i][j - 1] == 0)) || (i + 1 < mPuzzle.size() && (curNum == mPuzzle[i + 1][j] || mPuzzle[i + 1][j] == 0)) || (i - 1 >= 0 && (curNum == mPuzzle[i - 1][j] || mPuzzle[i - 1][j] == 0)))
            {
                return true;
            }
        }
    }
    return false;
}

void Game2048::moveLeft()
{
    for (int i = 0; i < 4; i++)
    {
        vector<bool> canMove(4, true);
        for (int k = 0; k < 4; k++)
        {
            for (int j = k; j > 0 && canMove[j - 1]; j--)
            {
                if (mPuzzle[i][j] == mPuzzle[i][j - 1] && mPuzzle[i][j] != 0)
                {
                    mPuzzle[i][j - 1] *= 2;
                    mCurrScore += mPuzzle[i][j - 1];
                    if (mPuzzle[i][j - 1] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[i][j] = 0;
                    canMove[j - 1] = false;
                    break;
                }
                else if (mPuzzle[i][j - 1] == 0)
                {
                    mPuzzle[i][j - 1] = mPuzzle[i][j];
                    mPuzzle[i][j] = 0;
                }
            }
        }
    }
    Game2048::addRandomNums();
}

void Game2048::moveRight()
{
    for (int i = 0; i < 4; i++)
    {
        vector<bool> canMove(4, true);
        for (int k = 4 - 1; k >= 0; k--)
        {
            for (int j = k; j < 4 - 1 && canMove[j + 1]; j++)
            {
                if (mPuzzle[i][j] == mPuzzle[i][j + 1] && mPuzzle[i][j] != 0)
                {
                    mPuzzle[i][j + 1] *= 2;
                    mCurrScore += mPuzzle[i][j + 1];
                    if (mPuzzle[i][j + 1] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[i][j] = 0;
                    canMove[j + 1] = false;
                    break;
                }
                else if (mPuzzle[i][j + 1] == 0)
                {
                    mPuzzle[i][j + 1] = mPuzzle[i][j];
                    mPuzzle[i][j] = 0;
                }
            }
        }
    }
    Game2048::addRandomNums();
}

void Game2048::moveUp()
{
    for (int j = 0; j < 4; j++)
    {
        vector<bool> canMove(4, true);
        for (int k = 0; k < 4; k++)
        {
            for (int i = k; i > 0 && canMove[i - 1]; i--)
            {
                if (mPuzzle[i][j] == mPuzzle[i - 1][j] && mPuzzle[i][j] != 0)
                {
                    mPuzzle[i - 1][j] *= 2;
                    mCurrScore += mPuzzle[i - 1][j];
                    if (mPuzzle[i - 1][j] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[i][j] = 0;
                    canMove[i - 1] = false;
                    break;
                }
                else if (mPuzzle[i - 1][j] == 0)
                {
                    mPuzzle[i - 1][j] = mPuzzle[i][j];
                    mPuzzle[i][j] = 0;
                }
            }
        }
    }
    Game2048::addRandomNums();
}

void Game2048::moveDown()
{
    for (int j = 0; j < 4; j++)
    {
        vector<bool> canMove(4, true);
        for (int k = 4 - 1; k >= 0; k--)
        {
            for (int i = k; i < 4 - 1 && canMove[i + 1]; i++)
            {
                if (mPuzzle[i][j] == mPuzzle[i + 1][j] && mPuzzle[i][j] != 0)
                {
                    mPuzzle[i + 1][j] *= 2;
                    mCurrScore += mPuzzle[i + 1][j];
                    if (mPuzzle[i + 1][j] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[i][j] = 0;
                    canMove[i + 1] = false;
                    break;
                }
                else if (mPuzzle[i + 1][j] == 0)
                {
                    mPuzzle[i + 1][j] = mPuzzle[i][j];
                    mPuzzle[i][j] = 0;
                }
            }
        }
    }
    Game2048::addRandomNums();
}