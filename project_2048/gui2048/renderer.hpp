#pragma once
#include "game2048.hpp"
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Renderer
{
    Game2048 &mGame;
    std::unordered_map<int, sf::Sprite> mTilesTextures;

public:
    Renderer(Game2048 &game);

    void render(sf::RenderWindow &window) const;
    void renderConsole() const;
    void renderFrames(sf::RenderWindow &window);
};