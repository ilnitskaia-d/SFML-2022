#include "game.hpp"

Game::Game(int tableSize)
    : mCircleR(0), mCircleC(0), mDir(Dirs::None), mTableSize(tableSize)
{
}

void Game::processEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed && mDir == Dirs::None)
        {
            if (event.key.code == sf::Keyboard::Right)
            {
                mDir = Dirs::Right;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                mDir = Dirs::Down;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                mDir = Dirs::Left;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                mDir = Dirs::Up;
            }
        }
    }
}

void Game::draw(sf::RenderWindow &window)
{
    int width = window.getSize().x;
    int height = window.getSize().y;
    float rectSize = std::min(width, height) / (2 * mTableSize);
    float leftTopX = width / 2.0f - rectSize * mTableSize / 2.0f;
    float leftTopY = height / 2.0f - rectSize * mTableSize / 2.0f;

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(rectSize, rectSize));
    rect.setFillColor(sf::Color::Blue);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(4);

    sf::CircleShape circle;
    circle.setRadius(rectSize / 2);
    circle.setFillColor(sf::Color::Red);

    for (int r = 0; r < mTableSize; ++r)
    {
        for (int c = 0; c < mTableSize; ++c)
        {
            rect.setPosition(sf::Vector2f(leftTopX + c * rectSize, leftTopY + r * rectSize));
            window.draw(rect);
        }
    }

    circle.setPosition(sf::Vector2f(leftTopX + mCircleC * rectSize, leftTopY + mCircleR * rectSize));
    window.draw(circle);
}

void Game::update()
{
    if (mDir == Dirs::Right)
    {
        ++mCircleC;
        if (mCircleC == mTableSize)
        {
            mCircleC--;
            mDir = Dirs::None;
        }
    }
    else if (mDir == Dirs::Down)
    {
        ++mCircleR;
        if (mCircleR == mTableSize)
        {
            mCircleR--;
            mDir = Dirs::None;
        }
    }
    else if (mDir == Dirs::Left)
    {
        --mCircleC;
        if (mCircleC == -1)
        {
            mCircleC++;
            mDir = Dirs::None;
        }
    }
    else if (mDir == Dirs::Up)
    {
        --mCircleR;
        if (mCircleR == -1)
        {
            mCircleR++;
            mDir = Dirs::None;
        }
    }
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    const sf::Time framesPerSec = sf::seconds(0.1f);
    sf::Time totalTime = sf::Time::Zero;
    sf::Clock clock;
    while (window.isOpen())
    {
        totalTime += clock.restart();
        if (totalTime > framesPerSec)
        {
            totalTime -= framesPerSec;
            update();
        }

        processEvent(window);

        window.clear();
        draw(window);

        window.display();
    }
}