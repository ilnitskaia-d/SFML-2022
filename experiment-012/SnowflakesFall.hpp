#pragma once
#include "ScreenSavers.hpp"
#include <vector>
#include <memory>

class SnowflakesFall : public ScreenSavers
{
public:
    SnowflakesFall(sf::RenderWindow &window);

    void draw(int dir) override;
};
