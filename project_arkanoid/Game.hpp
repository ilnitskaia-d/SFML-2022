#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Title.hpp"

class Block;

class Game
{
    sf::RenderWindow mWindow;
    std::vector<std::vector<std::string>> mLevels;
    std::vector<std::string> mTitles;
    std::vector<std::unique_ptr<Block>> mBlocks;
    Player mPlayer;
    Title mTitle;
    Ball mBall;
    int mCurLevel;
    sf::Time mTimeOfMagic;
    void (*mPtrEndingMagic)(void *);

    bool loadLevels();
    bool checkLevel();
    void loadBlocks(int level);

public:
    Game();
    void run();
    void increaseRacketSize();
    void restoreRacketSize();

    void setPtrEndingMagic(void *ptr)
    {
        mPtrEndingMagic = reinterpret_cast<void (*)(void *)>(ptr);
    }

    void setMagicDuration(int timeOfMagic)
    {
        mTimeOfMagic = sf::seconds(timeOfMagic);
    }
};