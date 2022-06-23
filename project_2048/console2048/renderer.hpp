#pragma once
#include "game2048.hpp"
#include <iomanip>
#include <iostream>

class Renderer
{
    Game2048 &mGame;
    Renderer(Game2048 &game)
        : mGame(game)
    {
    }

    void render() const
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::cout << std::setw(5) << mGame.getAt(i, j) << std::endl;
            }
        }
    }
};