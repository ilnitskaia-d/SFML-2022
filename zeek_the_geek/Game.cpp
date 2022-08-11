#include "Game.hpp"
#include "GameObj.hpp"
#include "MainCharacter.hpp"

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mCharacter(mWindow, mWindow.getSize().x / 2.0f, mWindow.getSize().y / 2.0f)
{
    mWindow.setVerticalSyncEnabled(true);
}

void Game::run()
{
    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
            }
        }

        mWindow.clear();
        mCharacter.draw();
        mWindow.display();
    }
}