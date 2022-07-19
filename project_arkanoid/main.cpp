#include <SFML/Graphics.hpp>

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

bool loadLevels(std::vector<std::vector<std::string>> &levels, std::vector<std::string> &titles)
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
        titles.push_back(line);

        if (!std::getline(level, line))
        {
            return false;
        }

        std::cout << line << std::endl;
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

        levels.push_back(curLevel);
    }
    return true;
}

bool checkLevel(std::vector<std::unique_ptr<Block>> &blocks)
{
    for (auto &block : blocks)
    {
        if (block->getState() >= 0)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");

    // const int WindowWidth = window.getSize().x;
    // const int WindowHeight = window.getSize().y;
    const sf::Time TimePerFrame = sf::seconds(0.01f);
    sf::Clock clock;
    sf::Time totalTime = sf::Time::Zero;

    std::vector<std::vector<std::string>> levels;
    std::vector<std::string> titles;
    loadLevels(levels, titles);

    std::vector<std::unique_ptr<Block>> blocks;
    float w = window.getSize().x / levels[0][0].size();
    float h = window.getSize().y / levels[0].size();
    int curLevel = 0;
    // for (auto level : levels)
    {
        for (int j = 0; j < levels[curLevel].size(); j++)
        {
            for (int i = 0; i < levels[curLevel][j].size(); i++)
            {
                if (levels[curLevel][j][i] == 'A')
                {
                    blocks.push_back(std::make_unique<Block>(window, i * w + 5, j * h + 5, w, h));
                }
            }
        }
    }

    Player player(window);
    Ball ball(window, blocks, player);

    std::cout << levels.size() << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        totalTime += clock.restart();
        while (totalTime > TimePerFrame)
        {
            totalTime -= TimePerFrame;
            ball.move(TimePerFrame.asSeconds());
        }

        player.move();

        window.clear();
        for (auto &block : blocks)
        {
            block->draw();
        }

        if (!checkLevel(blocks))
        {
            curLevel++;
            levels.clear();
            for (int j = 0; j < levels[curLevel].size(); j++)
            {
                for (int i = 0; i < levels[curLevel][j].size(); i++)
                {
                    if (levels[curLevel][j][i] == 'A')
                    {
                        blocks.push_back(std::make_unique<Block>(window, i * w + 5, j * h + 5, w, h));
                    }
                }
            }
        }

        player.draw();
        ball.draw();
        window.display();
    }
}
