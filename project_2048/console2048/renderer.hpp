#pragma once
#include "game2048.hpp"
#include <iomanip>
#include <iostream>

class Renderer
{
    Game2048 &mGame;

public:
    Renderer(Game2048 &game)
        : mGame(game)
    {
    }

    void render() const
    {
        std::cout << "Score: " << mGame.getCurrScore() << std::endl;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::cout << std::setw(5) << mGame.getAt(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};