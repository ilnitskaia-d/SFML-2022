#pragma once
#include "ScreenSavers.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class SnowflakesFall : public ScreenSavers
{
public:
    SnowflakesFall(sf::RenderWindow &window)
        : ScreenSavers(window)
    {
        for(int i = 0; i < mPartCount; i++)
        {
            
        }
    }

    void draw() override;
};
