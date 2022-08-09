#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Player.hpp"
#include "Title.hpp"
#include <memory>

class Ball
{
    sf::RenderWindow &mWindow;
    sf::CircleShape mBall;
    std::vector<std::unique_ptr<Block>> &mBlocks;
    Player &mPlayer;
    sf::Vector2f mSpeed;
    Title &mTitle;

public:
    Ball(sf::RenderWindow &window, std::vector<std::unique_ptr<Block>> &blocks, Player &player, Title &title);
    sf::Vector2f getPos();
    void draw();
    void move(float time);
};