#include "Game.hpp"
#include "../libs/random.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "Title.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>

using Random = effolkronium::random_static;

namespace
{
    void increaseRacketSize(void *ptr, void *ptr2)
    {
        Game *ptrToGame = reinterpret_cast<Game *>(ptr);
        ptrToGame->increaseRacketSize();
        ptrToGame->setMagicDuration(30);
        ptrToGame->setPtrEndingMagic(ptr2);
    }

    void restoreRacketSize(void *ptr)
    {
        Game *ptrToGame = reinterpret_cast<Game *>(ptr);
        ptrToGame->restoreRacketSize();
    }

    std::vector<void (*)(void *, void *)> startingMagic = {nullptr, increaseRacketSize};
    std::vector<void (*)(void *)> endingMagic = {nullptr, restoreRacketSize};
}

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mPlayer(mWindow), mBall(mWindow, mBlocks, mPlayer), mCurLevel(0), mTimeOfMagic(sf::seconds(0))
{
    mWindow.setMouseCursorVisible(false);
    loadLevels();
    loadBlocks(mCurLevel);
}

void Game::loadBlocks(int level)
{
    float w = mWindow.getSize().x / mLevels[level][0].size();
    float h = mWindow.getSize().y / mLevels[0].size();
    for (size_t j = 0; j < mLevels[level].size(); j++)
    {
        for (size_t i = 0; i < mLevels[level][j].size(); i++)
        {
            if (isalpha(mLevels[level][j][i]))
            {
                size_t index = mLevels[level][j][i] - 'A';
                mBlocks.push_back(std::make_unique<Block>(
                    this,
                    mWindow,
                    i * w + 5,
                    j * h + 5,
                    w,
                    h,
                    startingMagic[index], endingMagic[index]));
            }
        }
    }
}

bool Game::loadLevels()
{
    std::fstream level("data/levels.data");
    if (!level)
    {
        std::cout << "file not found" << std::endl;
        return false;
    }
    for (;;)
    {
        std::string line;
        if (!std::getline(level, line))
        {
            break;
        }
        mTitles.push_back(line);

        if (!std::getline(level, line))
        {
            return false;
        }

        int h;
        std::istringstream sinp(line);
        if (!(sinp >> h))
        {
            return false;
        }

        std::vector<std::string> curLevel;
        for (int i = 0; i < int(h); i++)
        {
            if (!std::getline(level, line))
            {
                return false;
            }
            curLevel.push_back(line);
        }

        mLevels.push_back(curLevel);
    }

    return true;
}

bool Game::checkLevel()
{
    for (auto &block : mBlocks)
    {
        if (block->getState() >= 0)
        {
            return true;
        }
    }
    return false;
}

void Game::run()
{
    const sf::Time TimePerFrame = sf::seconds(0.01f);
    sf::Clock clock;
    sf::Time totalTime = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                mWindow.close();
            }
        }

        totalTime += clock.restart();
        while (totalTime > TimePerFrame)
        {
            totalTime -= TimePerFrame;
            mBall.move(TimePerFrame.asSeconds());
            if (mTimeOfMagic > sf::seconds(0))
            {
                mTimeOfMagic -= TimePerFrame;
                if (mTimeOfMagic <= sf::seconds(0))
                {
                    mPtrEndingMagic(this);
                }
            }
        }

        mPlayer.move();

        mWindow.clear();
        for (auto &block : mBlocks)
        {
            block->draw();
        }

        if (!checkLevel())
        {
            if (mCurLevel < int(mLevels.size()) - 1)
            {
                mCurLevel++;
                loadBlocks(mCurLevel);
            }
        }

        // mTitle.draw();
        mPlayer.draw();
        mBall.draw();
        mWindow.display();
    }
}

void Game::increaseRacketSize()
{
    mPlayer.increaseSize(mPlayer.getSize().x / 2);
}

void Game::restoreRacketSize()
{
    mPlayer.restoreSize(mPlayer.getSize().x / 2);
}
