#include <SFML/Graphics.hpp>

#include "../libs/random.hpp"
#include <algorithm>
#include <iostream>
#include "Ball.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include <math.h>

using Random = effolkronium::random_static;

int main()
{

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);

    // const int WindowWidth = window.getSize().x;
    // const int WindowHeight = window.getSize().y;

    const sf::Time TimePerFrame = sf::seconds(0.01f);
    sf::Clock clock;
    sf::Time totalTime = sf::Time::Zero;

    Block block(window);
    Player player(window);
    Ball ball(window, block, player);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        totalTime += clock.restart();
        while (totalTime > TimePerFrame)
        {
            totalTime -= TimePerFrame;
            ball.move(TimePerFrame.asSeconds());
        }

        player.move();

        window.clear();
        block.draw();
        player.draw();
        ball.draw();
        window.display();
    }
}