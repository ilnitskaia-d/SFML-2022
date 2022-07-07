#include "SnowflakesFall.hpp"
#include "../libs/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

SnowflakesFall::SnowflakesFall(sf::RenderWindow &window)
    : ScreenSavers(window)
{
    int width = mWindow.getSize().x;
    for (int i = 0; i < mPartCount; i++)
    {
        int x = Random::get(0, width);
        mCoords.push_back({x, 10});
    }
}

void SnowflakesFall::draw(int dir)
{
    float size = 5;
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Red);
    rect.setSize(sf::Vector2f(size, size));
    {
        for(auto &p : mCoords)
        {
            rect.setPosition(sf::Vector2f(p.first, p.second + dir));
            mWindow.draw(rect);
        }
    }
}