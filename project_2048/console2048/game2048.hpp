#pragma once
#include <vector>

class Game2048
{
    std::vector<std::vector<int>> mPuzzle;
    int mGoal;
    int mCurrScore;
    bool mWin;

public:
    Game2048(int goal = 16);
    void addRandomNums();
    int getAt(int r, int c) const;
    bool getWinStatus() const;
    int getCurrScore() const;
    bool canMove();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};
