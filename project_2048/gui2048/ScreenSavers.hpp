#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class ScreenSavers
{
protected:
    sf::RenderWindow &mWindow;
    int mPartCount;
    std::vector<std::pair<int, int>> mCoords;

public:
    ScreenSavers(sf::RenderWindow &window)
        : mWindow(window), mPartCount(30), mCoords(mPartCount)
    {
    }

    virtual void draw() = 0;
};