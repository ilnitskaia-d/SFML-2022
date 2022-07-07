#include "SnowflakesFall.hpp"
#include "../../libs/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

SnowflakesFall::SnowflakesFall(sf::RenderWindow &window)
    : ScreenSavers(window), mSizes(mPartCount)
{
    int width = mWindow.getSize().x;
    int height = mWindow.getSize().y;
    for (int i = 0; i < mPartCount; i++)
    {
        int x = Random::get(0, width);
        int y = Random::get(-10, -height);
        mCoords[i] = {x, y};
        mSizes[i] = Random::get(5, 15);
    }
}

void SnowflakesFall::draw()
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);
    for (int i = 0; i < mPartCount; i++)
    {
        rect.setSize(sf::Vector2f(mSizes[i], mSizes[i]));
        rect.setPosition(sf::Vector2f(mCoords[i].first, mCoords[i].second));
        mCoords[i].second++;
        if (mCoords[i].second == (int)(mWindow.getSize().y))
        {
            mCoords[i].second = Random::get(-10, -20);
        }
        mWindow.draw(rect);
    }
}