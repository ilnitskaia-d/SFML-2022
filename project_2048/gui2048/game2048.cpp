#include "game2048.hpp"
#include "..\..\libs\random.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using Random = effolkronium::random_static;

Game2048::Game2048(sf::RenderWindow &window, int goal)
    : mPuzzle(4, vector<int>(4)), mGoal(goal), mCurrScore(0), mWin(false), mIsMoving(false), mWindow(window)
{
    vector<int> nums = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    ifstream finp("best.data");
    for (int n : nums)
    {
        int inp;
        finp >> inp;
        mBestScore[n] = inp;
    }
    addRandomNums();
    addRandomNums();
}

Game2048::~Game2048()
{
    ofstream fout("best.data");

    for (auto &[k, n] : mBestScore)
    {
        fout << n << "\n";
    }

    for (auto el : mBestScore)
    {
        cout << el.first << " " << el.second << endl;
    }
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

vector<vector<int>> Game2048::popFrame()
{
    vector<vector<int>> frame = mFrames.front();
    mFrames.pop();
    return frame;
}

bool Game2048::isFramesEmpty()
{
    return mFrames.empty();
}

vector<vector<int>> Game2048::getNextFrame()
{
    if (!isFramesEmpty())
    {
        return popFrame();
    }

    return mPuzzle;
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
    vector<vector<bool>> merged(4, vector<bool>(4, true));
    for (int step = 0; step < 3; ++step)
    {
        bool isChanged = false;
        for (int r = 0; r < 4; r++)
        {
            for (int c = 1; c < 4; c++)
            {
                if (mPuzzle[r][c] != 0 && mPuzzle[r][c - 1] == 0)
                {
                    mPuzzle[r][c - 1] = mPuzzle[r][c];
                    mPuzzle[r][c] = 0;
                    isChanged = true;
                }
                else if (mPuzzle[r][c] == mPuzzle[r][c - 1] && merged[r][c - 1] && merged[r][c])
                {
                    mPuzzle[r][c - 1] *= 2;
                    mCurrScore += mPuzzle[r][c - 1];
                    mBestScore[mGoal] = max(mCurrScore, mBestScore[mGoal]);
                    if (mPuzzle[r][c - 1] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[r][c] = 0;
                    merged[r][c - 1] = false;
                    isChanged = true;
                }
            }
        }
        if (isChanged)
        {
            mFrames.push(mPuzzle);
        }
    }
    addRandomNums();
    mIsMoving = false;
}

void Game2048::moveRight()
{
    vector<vector<bool>> merged(4, vector<bool>(4, true));
    for (int step = 0; step < 3; ++step)
    {
        bool isChanged = false;
        for (int r = 0; r < 4; r++)
        {
            for (int c = 2; c >= 0; c--)
            {
                if (mPuzzle[r][c] != 0 && mPuzzle[r][c + 1] == 0)
                {
                    mPuzzle[r][c + 1] = mPuzzle[r][c];
                    mPuzzle[r][c] = 0;
                    isChanged = true;
                }
                else if (mPuzzle[r][c] == mPuzzle[r][c + 1] && merged[r][c + 1] && merged[r][c])
                {
                    mPuzzle[r][c + 1] *= 2;
                    mCurrScore += mPuzzle[r][c + 1];
                    mBestScore[mGoal] = max(mCurrScore, mBestScore[mGoal]);
                    if (mPuzzle[r][c + 1] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[r][c] = 0;
                    merged[r][c + 1] = false;
                    isChanged = true;
                }
            }
        }
        if (isChanged)
        {
            mFrames.push(mPuzzle);
        }
    }
    addRandomNums();
    mIsMoving = false;
}

void Game2048::moveUp()
{
    vector<vector<bool>> merged(4, vector<bool>(4, true));
    for (int step = 0; step < 3; ++step)
    {
        bool isChanged = false;
        for (int c = 0; c < 4; c++)
        {
            for (int r = 1; r < 4; r++)
            {
                if (mPuzzle[r][c] != 0 && mPuzzle[r - 1][c] == 0)
                {
                    mPuzzle[r - 1][c] = mPuzzle[r][c];
                    mPuzzle[r][c] = 0;
                    isChanged = true;
                }
                else if (mPuzzle[r][c] == mPuzzle[r - 1][c] && merged[r - 1][c] && merged[r][c])
                {
                    mPuzzle[r - 1][c] *= 2;
                    mCurrScore += mPuzzle[r - 1][c];
                    mBestScore[mGoal] = max(mCurrScore, mBestScore[mGoal]);
                    if (mPuzzle[r - 1][c] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[r][c] = 0;
                    merged[r - 1][c] = false;
                    isChanged = true;
                }
            }
        }
        if (isChanged)
        {
            mFrames.push(mPuzzle);
        }
    }
    addRandomNums();
    mIsMoving = false;
}

void Game2048::moveDown()
{
    vector<vector<bool>> merged(4, vector<bool>(4, true));
    for (int step = 0; step < 3; ++step)
    {
        bool isChanged = false;
        for (int c = 0; c < 4; c++)
        {
            for (int r = 2; r >= 0; r--)
            {
                if (mPuzzle[r][c] != 0 && mPuzzle[r + 1][c] == 0)
                {
                    mPuzzle[r + 1][c] = mPuzzle[r][c];
                    mPuzzle[r][c] = 0;
                    isChanged = true;
                }
                else if (mPuzzle[r][c] == mPuzzle[r + 1][c] && merged[r + 1][c] && merged[r][c])
                {
                    mPuzzle[r + 1][c] *= 2;
                    mCurrScore += mPuzzle[r + 1][c];
                    mBestScore[mGoal] = max(mCurrScore, mBestScore[mGoal]);
                    if (mPuzzle[r + 1][c] == mGoal)
                    {
                        mWin = true;
                    }
                    mPuzzle[r][c] = 0;
                    merged[r + 1][c] = false;
                    isChanged = true;
                }
            }
        }
        if (isChanged)
        {
            mFrames.push(mPuzzle);
        }
    }
    addRandomNums();
    mIsMoving = false;
}

int Game2048::getBestScore() const
{
    return mBestScore.find(mGoal)->second;
}

void Game2048::eventProcess()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                moveLeft();
                mIsMoving = true;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                moveRight();
                mIsMoving = true;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                moveUp();
                mIsMoving = true;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                moveDown();
                mIsMoving = true;
            }
        }
    }
}