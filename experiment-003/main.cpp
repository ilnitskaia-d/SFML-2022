#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("data/AlamedaScript.otf");

    sf::Text text("hello, world", font);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Red);
    float textX = window.getSize().x / 2 - text.getLocalBounds().width / 2;
    float textY = window.getSize().y / 2 - text.getLocalBounds().height;
    text.setPosition(sf::Vector2f(textX, textY));

    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile("data/Explosion.wav"))
    {
        std::cout << "data/Explosion.wav not found" << std::endl;
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(soundBuffer);
    sound.setVolume(100);

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
                // int step = shape.getRadius() * 2;
                // if (event.key.code == sf::Keyboard::Left)
                // {
                //     shapeX -= step;
                // }
                // else if (event.key.code == sf::Keyboard::Right)
                // {
                //     shapeX += step;
                // }
                // else if (event.key.code == sf::Keyboard::Up)
                // {
                //     shapeY -= step;
                // }
                // else if (event.key.code == sf::Keyboard::Down)
                // {
                //     shapeY += step;
                // }
                // shape.setPosition(sf::Vector2f(shapeX, shapeY));
                // sound.play();
#ifdef AUCA_DEBUG
                std::clog << sound.getVolume() << std::endl;
#endif
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }

#ifdef AUCA_DEBUG
    std::clog << "ok" << std::endl;
#endif
}