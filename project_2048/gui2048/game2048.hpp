#pragma once
#include <vector>
#include <map>
#include <queue>
#include <SFML/Graphics.hpp>

class Game2048
{
    std::vector<std::vector<int>> mPuzzle;
    int mGoal;
    int mCurrScore;
    bool mWin;
    std::map<int, int> mBestScore;
    std::queue<std::vector<std::vector<int>>> mFrames;
    bool mIsMoving;
    sf::RenderWindow &mWindow;

private:
    void push();

public:
    Game2048(sf::RenderWindow &window, int goal = 16);
    ~Game2048();

    void addRandomNums();
    int getAt(int r, int c) const;
    bool getWinStatus() const;
    int getCurrScore() const;

    std::vector<std::vector<int>> popFrame();
    bool isFramesEmpty();
    std::vector<std::vector<int>> getNextFrame();
    
    bool canMove();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    int getBestScore() const;

    void eventProcess();
};
