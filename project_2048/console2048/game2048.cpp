#include "game2048.hpp"
#include "..\..\libs\random.hpp"

using namespace std;
using Random = effolkronium::random_static;

Game2048::Game2048(int goal)
    : mPuzzle(4, vector<int>(4)), mGoal(goal), mCurrScore(0)
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