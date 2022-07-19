#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Player.hpp"
#include <memory>

class Ball
{
    sf::RenderWindow &mWindow;
    sf::CircleShape mBall;
    std::vector<std::unique_ptr<Block>> &mBlocks;
    Player &mPlayer;
    sf::Vector2f mSpeed;

public:
    Ball(sf::RenderWindow &window, std::vector<std::unique_ptr<Block>> &blocks, Player &player);
    sf::Vector2f getPos();
    void draw();
    void move(float time);
};