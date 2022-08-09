#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Title
{
    sf::RenderWindow &mWindow;
    sf::RectangleShape mLife;
    sf::Text mScoreText;

public:
    int mScore;
    int mLives;

    Title(sf::RenderWindow &window)
        : mWindow(window), mScore(0), mLives(3)
    {

        std::cout << "-----------works----------" << std::endl;
        mScoreText.setString(std::to_string(mScore));
        mScoreText.setCharacterSize(50);
        mScoreText.setFillColor(sf::Color::White);
        mScoreText.setPosition(sf::Vector2f(10, 10));
        mLife.setFillColor(sf::Color::White);
        mLife.setSize(sf::Vector2f(30, 10));
        mLife.setPosition(sf::Vector2f(mWindow.getSize().x - 40, 10));
    }

    void setFont(sf::Font &font)
    {

        mScoreText.setFont(font);
    }

    void draw()
    {
        mWindow.draw(mScoreText);

        for (int i = 0; i < mLives; i++)
        {
            mLife.setPosition(sf::Vector2f(mWindow.getSize().x - (i * 40), 10));
            mWindow.draw(mLife);
        }
    }
};