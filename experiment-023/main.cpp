#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    float winSizeX = window.getSize().x * 2;
    float winSizeY = window.getSize().y * 2;

    sf::CircleShape shape1;
    shape1.setRadius(100);
    shape1.setFillColor(sf::Color::Red);
    float shapeX = winSizeX / 4 - shape1.getRadius();
    float shapeY = winSizeY / 4 - shape1.getRadius();
    shape1.setPosition(sf::Vector2f(shapeX, shapeY));

    sf::CircleShape shape2;
    shape2.setRadius(100);
    shape2.setFillColor(sf::Color::Yellow);
    shapeX = winSizeX / 2 - shape2.getRadius();
    shapeY = winSizeY / 2 - shape2.getRadius();
    shape2.setPosition(sf::Vector2f(shapeX, shapeY));

    sf::CircleShape shape3;
    shape3.setRadius(100);
    shape3.setFillColor(sf::Color::Blue);
    shapeX = winSizeX / 4 + shape3.getRadius();
    shapeY = winSizeY - winSizeY / 4 - shape3.getRadius();
    shape3.setPosition(sf::Vector2f(shapeX, shapeY));

    sf::CircleShape shape4;
    shape4.setRadius(100);
    shape4.setFillColor(sf::Color::Green);
    shapeX = winSizeX - winSizeX / 4 - shape4.getRadius();
    shapeY = winSizeY - winSizeY / 4 - shape4.getRadius();
    shape4.setPosition(sf::Vector2f(shapeX, shapeY));

    shapeX = winSizeX / 4;
    shapeY = winSizeY / 4;
    sf::RectangleShape rect(sf::Vector2f(100, 100));
    rect.setOrigin(50, 50);
    rect.setPosition(shapeX, shapeY);
    rect.setFillColor(sf::Color::Cyan);

    sf::View view(sf::Vector2f(shapeX, shapeY), sf::Vector2f(window.getSize().x, window.getSize().y));
    window.setView(view);

    sf::View viewPanel(sf::Vector2f(shapeX, shapeY), sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Font font;
    font.loadFromFile("data/FONT.TTF");
    sf::Text textCoords;
    textCoords.setFont(font);
    textCoords.setFillColor(sf::Color::White);
    textCoords.setCharacterSize(50);
    textCoords.setPosition(0, 0);
    textCoords.setString("x: " + std::to_string(shapeX) + " y: " + std::to_string(shapeY));

    sf::RectangleShape panel;
    panel.setFillColor(sf::Color(150, 150, 150));
    panel.setSize(sf::Vector2f(winSizeX, textCoords.getLocalBounds().height * 1.5f));

    sf::View viewMap(sf::Vector2f(winSizeX / 2, winSizeY / 2), sf::Vector2f(winSizeX, winSizeY));
    viewMap.setViewport(sf::FloatRect(0.75f, 0.75f, 0.25f, 0.25f));

    sf::RectangleShape rectFill(viewMap.getSize());
    rectFill.setPosition(0, 0);
    rectFill.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                int step = rect.getSize().x / 2;
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (shapeX - step > rect.getSize().x && shapeX - step < winSizeX - rect.getSize().x)
                    {
                        shapeX -= step;
                        if (shapeX - step > view.getSize().x / 2 && shapeX - step < winSizeX - view.getSize().x / 2)
                            view.move(-step, 0);
                    }
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (shapeX + step > rect.getSize().x && shapeX + step < winSizeX - rect.getSize().x)
                    {
                        shapeX += step;
                        if (shapeX + step > view.getSize().x / 2 && shapeX + step < winSizeX - view.getSize().x / 2)
                            view.move(step, 0);
                    }
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    if (shapeY - step > 0 && shapeY - step < winSizeY - rect.getSize().y)
                    {
                        shapeY -= step;
                        if (shapeY - step > view.getSize().y / 2 && shapeY - step < winSizeY - view.getSize().y / 2)
                            view.move(0, -step);
                    }
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (shapeY + step > 0 && shapeY + step < winSizeY - rect.getSize().y)
                    {
                        shapeY += step;
                        if (shapeY + step > view.getSize().y / 2 && shapeY + step < winSizeY - view.getSize().y / 2)
                            view.move(0, step);
                    }
                }
                rect.setPosition(sf::Vector2f(shapeX, shapeY));
                textCoords.setString("x: " + std::to_string(shapeX) + " y: " + std::to_string(shapeY));
            }
        }

        window.clear();
        window.setView(view);
        window.draw(shape1);
        window.draw(shape2);
        window.draw(shape3);
        window.draw(shape4);
        window.draw(rect);

        window.setView(viewMap);
        window.draw(rectFill);
        window.draw(shape1);
        window.draw(shape2);
        window.draw(shape3);
        window.draw(shape4);
        window.draw(rect);

        window.setView(viewPanel);
        panel.setPosition(0, 0);
        window.draw(panel);
        panel.setPosition(window.getSize().x - panel.getSize().x, 0);
        window.draw(panel);
        window.draw(textCoords);

        window.display();
    }
}