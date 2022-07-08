#pragma once
#include "ScreenSavers.hpp"
#include <vector>

class SnowflakesFall : public ScreenSavers
{
    std::vector<int> mSizes;
public:
    SnowflakesFall(sf::RenderWindow &window);

    void draw() override;
};
