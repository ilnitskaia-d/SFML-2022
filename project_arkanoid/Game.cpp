#include "Game.hpp"
#include "../libs/random.hpp"
#include <algorithm>
#include <iostream>
#include "Ball.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include <memory>
#include <math.h>
#include <fstream>
#include <sstream>

using Random = effolkronium::random_static;

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mPlayer(mWindow),
      mBall(mWindow, mBlocks, mPlayer), mCurLevel(0)
{
    loadLevels();
    loadBlocks(mCurLevel);
}

void Game::loadBlocks(int level)
{
    float w = mWindow.getSize().x / mLevels[level][0].size();
    float h = mWindow.getSize().y / mLevels[0].size();
    for (int j = 0; j < mLevels[level].size(); j++)
    {
        for (int i = 0; i < mLevels[level][j].size(); i++)
        {
            if (mLevels[level][j][i] == 'A')
            {
                mBlocks.push_back(std::make_unique<Block>(mWindow, i * w + 5, j * h + 5, w, h));
            }
        }
    }
}

bool Game::loadLevels()
{
    std::fstream level("levels.data");
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
        for (int i = 0; i < h; i++)
        {
            if (!std::getline(level, line))
            {
                return false;
            }
            curLevel.push_back(line);
        }

        mLevels.push_back(curLevel);
    }

    for (int nLevel = 0; nLevel < mLevels.size(); nLevel++)
    {
        for (int j = 0; j < mLevels[nLevel].size(); j++)
        {
            std::cout << mLevels[nLevel][j] << std::endl;
        }
        std::cout << std::endl;
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
        }

        mPlayer.move();

        mWindow.clear();
        for (auto &block : mBlocks)
        {
            block->draw();
        }

        if (!checkLevel())
        {
            if (mCurLevel < mLevels.size() - 1)
            {
                mCurLevel++;
                loadBlocks(mCurLevel);
            }
        }

        mPlayer.draw();
        mBall.draw();
        mWindow.display();
    }
}