#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include <iostream>

int main()
{
    const int tableSize = 10;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    int width = window.getSize().x;
    int height = window.getSize().y;
    float rectSize = std::min(width, height) / (2 * tableSize);
    float leftTopX = width / 2.0f - rectSize * tableSize / 2.0f;
    float leftTopY = height / 2.0f - rectSize * tableSize / 2.0f;

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(rectSize, rectSize));
    rect.setFillColor(sf::Color::Blue);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(4);

    sf::CircleShape circle;
    circle.setRadius(rectSize / 2);
    float circleR = 0;
    float circleC = 0;
    circle.setFillColor(sf::Color::Red);

    float dir = 0;

    const sf::Time framesPerSec = sf::seconds(0.1f);
    sf::Time totalTime = sf::Time::Zero;
    sf::Clock clock;
    while (window.isOpen())
    {
        totalTime += clock.restart();
        if (totalTime > framesPerSec)
        {
            totalTime -= framesPerSec;
            if (dir == 0)
            {
                ++circleC;
                if (circleC == tableSize)
                {
                    dir = 1;
                    circleC = tableSize - 1;
                    circleR++;
                }
            }
            else if (dir == 1)
            {
                ++circleR;
                if (circleR == tableSize)
                {
                    dir = 2;
                    circleR = tableSize - 1;
                    circleC--;
                }
            }
            else if (dir == 2)
            {
                --circleC;
                if (circleC == -1)
                {
                    dir = 3;
                    circleC = 0;
                    circleR--;
                }
            }
            else if (dir == 3)
            {
                --circleR;
                if (circleR == -1)
                {
                    dir = 0;
                    circleR = 0;
                    circleC++;
                }
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
            }
        }
        window.clear();

        for (int r = 0; r < tableSize; ++r)
        {
            for (int c = 0; c < tableSize; ++c)
            {
                rect.setPosition(sf::Vector2f(leftTopX + c * rectSize, leftTopY + r * rectSize));
                window.draw(rect);
            }
        }

        circle.setPosition(sf::Vector2f(leftTopX + circleC * rectSize, leftTopY + circleR * rectSize));
        window.draw(circle);

        window.display();
    }

#ifdef AUCA_DEBUG
    std::clog << "ok" << std::endl;
#endif
}