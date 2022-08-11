#include "Game.hpp"
#include "MainCharacter.hpp"

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mField(mWindow), mCharacter(mWindow, mField, mWindow.getSize().x / 2.0f, mWindow.getSize().y / 2.0f)
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
            else
            {
                mCharacter.move();
            }
        }

        mWindow.clear();
        mField.draw();
        mCharacter.draw();
        mWindow.display();
    }
}