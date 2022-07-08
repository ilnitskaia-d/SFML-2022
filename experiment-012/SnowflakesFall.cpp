#include "SnowflakesFall.hpp"
#include "../libs/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

SnowflakesFall::SnowflakesFall(sf::RenderWindow &window)
    : ScreenSavers(window), mSizes(mPartCount)
{
    int width = mWindow.getSize().x;
    int height = mWindow.getSize().y;
    for (int i = 0; i < mPartCount; i++)
    {
        // int x = Random::get(0, width);
        // int y = Random::get(-10, -height);
        mCoords[i] = {width / 2, height / 2};
        // mSizes[i] = Random::get(5, 15);
    }
}

void SnowflakesFall::draw()
{
    // vector<int> dx = {0, - 1, 0, 1};
    sf::RectangleShape rect;
    int sizeX = 50;
    int sizeY = 10;
    for (int i = 0; i < mPartCount; i++)
    {
        // rect.setSize(sf::Vector2f(mSizes[i], mSizes[i]));
        rect.setSize(sf::Vector2f(sizeX, sizeY));
        // for (int j = 1; j < 5; j++)
        {
            rect.setFillColor(sf::Color::White);
            rect.setRotation(0);
            rect.setPosition(sf::Vector2f(mCoords[i].first - sizeX / 2, mCoords[i].second - sizeY / 2));
            mWindow.draw(rect);

            rect.setFillColor(sf::Color::Red);
            rect.setRotation(45);
            rect.setPosition(sf::Vector2f(mCoords[i].first + sizeX / 3, mCoords[i].second - sizeX / 3));
            mWindow.draw(rect);

            rect.setFillColor(sf::Color::Blue);
            rect.setRotation(90);
            rect.setPosition(sf::Vector2f(mCoords[i].first + sizeY / 2, mCoords[i].second - sizeX / 2));
            mWindow.draw(rect);

            rect.setFillColor(sf::Color::Green);
            rect.setRotation(135);
            rect.setPosition(sf::Vector2f(mCoords[i].first, mCoords[i].second));
            mWindow.draw(rect);
        }

        // mCoords[i].second++;
        // if (mCoords[i].second == (int)(mWindow.getSize().y))
        // {
        //     mCoords[i].second = Random::get(-10, -20);
        // }
    }
}