#pragma once
#include <vector>
#include <map>
#include <queue>

class Game2048
{
    std::vector<std::vector<int>> mPuzzle;
    int mGoal;
    int mCurrScore;
    bool mWin;
    std::map<int, int> mBestScore;
    std::queue<std::vector<std::vector<int>>> mFrames;

private:
    void push();

public:
    Game2048(int goal = 16);
    ~Game2048();
    void addRandomNums();
    int getAt(int r, int c) const;
    bool getWinStatus() const;
    int getCurrScore() const;
    std::vector<std::vector<int>> popFrame();
    bool canMove();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    int getBestScore() const;
    bool isFramesEmpty();
};
