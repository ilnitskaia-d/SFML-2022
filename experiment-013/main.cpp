#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Ball.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Player player(window);
    Ball ball(window);

    // const sf::Time framesPerSec = sf::seconds(0.001f);
    // sf::Time totalTime = sf::Time::Zero;
    // sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            player.move();
        }

        window.clear();
        player.draw();
        ball.draw();
        window.display();
    }
}