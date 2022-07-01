#pragma once
#include "game2048.hpp"
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

class Renderer
{
    Game2048 &mGame;
    sf::RenderWindow &mWindow;
    float mBlockSize;

public:
    Renderer(Game2048 &game, sf::RenderWindow &window);

    void render() const;
    void renderConsole() const;
    void renderFrames(sf::RenderWindow &window);
};