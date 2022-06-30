#pragma once
#include <SFML/Graphics.hpp>

class Game
{
    enum class Dirs
    {
        None,
        Right,
        Down,
        Left,
        Up
    };

    int mTileSize;
    float mCircleR;
    float mCircleC;
    Dirs mDir;
    int mTableSize;

public:
    Game(int tableSize);

    void run();
    void processEvent(sf::RenderWindow &window);
    void update();
    void draw(sf::RenderWindow &window);
};