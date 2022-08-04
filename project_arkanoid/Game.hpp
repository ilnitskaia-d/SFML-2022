#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "Player.hpp"
#include "Ball.hpp"

class Game
{
    sf::RenderWindow mWindow;
    std::vector<std::vector<std::string>> mLevels;
    std::vector<std::string> mTitles;
    std::vector<std::unique_ptr<Block>> mBlocks;
    Player mPlayer;
    Ball mBall;
    int mCurLevel;

    bool loadLevels();
    bool checkLevel();
    void loadBlocks(int level);

public:
    Game();
    void run();
};