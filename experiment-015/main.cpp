#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "..\libs\random.hpp"
#include <iostream>
#include <vector>

using Random = effolkronium::random_static;

class Star
{
private:
    sf::CircleShape mBall;
    sf::RenderWindow &mWindow;
    sf::Vector2f mPos;
    sf::Vector2f mVel;

    void init()
    {
        mBall.setRadius(10);

        float red = Random::get(0, 255);
        float green = Random::get(0, 255);
        float blue = Random::get(0, 255);
        mBall.setFillColor(sf::Color(red, green, blue));

        float xCenter = mWindow.getSize().x / 2;
        float yCenter = mWindow.getSize().y / 2;

        float x = Random::get(0.0f, (float)mWindow.getSize().x);
        float y = Random::get(0.0f, (float)mWindow.getSize().y);
        mPos.x = x;
        mPos.y = y;

        float dx = x - xCenter;
        float dy = y - yCenter;

        float r = sqrt(dx * dx + dy * dy);
        float v = r / 80;

        mVel.x = v * dx / r;
        mVel.y = v * dy / r;
    }

public:
    Star(sf::RenderWindow &window)
        : mWindow(window)
    {
        init();
    }

    void move()
    {
        mPos += mVel;
        if (mPos.x > mWindow.getSize().x || mPos.x < 0 || mPos.y > mWindow.getSize().y || mPos.y < 0)
        {
            init();
        }
    }

    void draw()
    {
        mBall.setPosition(mPos);
        mWindow.draw(mBall);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    int n = 100;

    std::vector<Star> stars;
    sf::RectangleShape rect(sf::Vector2f(window.getSize().x, window.getSize().y));
    rect.setFillColor(sf::Color(0, 0, 0, 80));

    stars.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        stars.emplace_back(window);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.draw(rect);
        for (size_t i = 0; i < stars.size(); i++)
        {
            stars[i].move();
            stars[i].draw();
        }
    }
    window.display();
}
