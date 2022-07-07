#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class ScreenSavers
{
protected:
    sf::RenderWindow &mWindow;
    int mPartCount;
    std::vector<std::unique_ptr<sf::Drawable>> mParts;

public:
    ScreenSavers(sf::RenderWindow &window)
        : mWindow(window), mPartCount(30)
    {
    }

    virtual void draw();
};