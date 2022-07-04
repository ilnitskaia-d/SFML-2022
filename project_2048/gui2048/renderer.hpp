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
    sf::Font &mFont;
    sf::Text nameText;
    sf::Text goalText;
    sf::Text bestScoreText;
    sf::Text currScoreText;

public:
    Renderer(Game2048 &game, sf::RenderWindow &window, sf::Font &font);

    void renderText();
    void render();
};