#include <SFML/Graphics.hpp>

#include "../libs/random.hpp"
#include <algorithm>
#include <iostream>
#include "Ball.hpp"
#include "Block.hpp"
#include <math.h>

using Random = effolkronium::random_static;

enum class States
{
    SetPos,
    SetDir,
    Move
};

int main()
{

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);

    const int WindowWidth = window.getSize().x;
    const int WindowHeight = window.getSize().y;

    const float SpeedValue = std::min(WindowWidth, WindowHeight);

    const sf::Time TimePerFrame = sf::seconds(0.01f);
    sf::Clock clock;
    sf::Time totalTime = sf::Time::Zero;

    Block block(window);

    Ball ball(window, block);
    sf::Vertex points[2];
    States curState = States::SetPos;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (curState == States::SetPos && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                ball.setPos();
            }
            else if (curState == States::SetPos && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                curState = States::SetDir;
                points[0].position.x = sf::Mouse::getPosition().x;
                points[0].position.y = sf::Mouse::getPosition().y;

                points[1].position.x = sf::Mouse::getPosition().x;
                points[1].position.y = sf::Mouse::getPosition().y;
            }
            else if (curState == States::SetDir && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                points[1].position.x = sf::Mouse::getPosition().x;
                points[1].position.y = sf::Mouse::getPosition().y;
            }
            else if (curState == States::SetDir && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                curState = States::Move;
                float dx = sf::Mouse::getPosition().x - ball.getPos().x;
                float dy = sf::Mouse::getPosition().y - ball.getPos().y;
                float length = sqrt(dx * dx + dy * dy);
                sf::Vector2f speed(SpeedValue * dx / length, SpeedValue * dy / length);
                ball.setSpeed(speed);
            }
        }

        totalTime += clock.restart();
        while (totalTime > TimePerFrame)
        {
            totalTime -= TimePerFrame;

            if (curState == States::Move)
            {
                ball.move(TimePerFrame.asSeconds());
            }
        }

        window.clear();
        if (curState == States::SetDir)
        {
            window.draw(points, 2, sf::Lines);
        }
        block.draw();
        ball.draw();
        window.display();
    }
}