#pragma once
#include "game2048.hpp"
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>

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
    }

    void renderFrames()
    {
    }
};