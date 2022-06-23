#pragma once
#include <vector>

class Game2048
{
    std::vector<std::vector<int>> mPuzzle;
    int mCurrScore;
    int mGoal;
    
public:
    Game2048(int goal = 16);
    void addRandomNums();
    int getAt(int r, int c) const;
}
