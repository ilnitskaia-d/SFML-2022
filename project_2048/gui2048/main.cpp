#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "game2048.hpp"
#include "renderer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    int goal = 0;

    if (argc == 1)
    {
        goal = 16;
    }
    else if (argc == 2)
    {
        int inp;
        char ch;
        istringstream sinp(argv[1]);
        if (sinp >> inp && !(sinp >> ch))
        {
            if (binary_search(v.begin(), v.end(), inp))
            {
                goal = inp;
            }
            else
            {
                cout << "Can't use goal of : " << inp << endl;
                exit(1);
            }
        }

        if (goal == 0)
        {
            goal = 16;
        }
    }
    else
    {
        cout << "Wrong input\n";
        exit(1);
    }
    sf::Font font;
    font.loadFromFile("data/BULKYPIX.TTF");

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    Game2048 game(window, goal);
    Renderer renderer(game, window, font);
    window.setVerticalSyncEnabled(true);
    renderer.render();

    sf::Text winningText("Congrats!!!", font);
    winningText.setCharacterSize(80);
    winningText.setFillColor(sf::Color::Magenta);

    sf::Text losingText("You lost", font);
    losingText.setCharacterSize(80);
    losingText.setFillColor(sf::Color::Red);

    float textX1 = window.getSize().x / 2 - winningText.getLocalBounds().width / 2;
    float textY1 = window.getSize().y / 2 - winningText.getLocalBounds().height;
    winningText.setPosition(sf::Vector2f(textX1, textY1));
    float textX2 = window.getSize().x / 2 - losingText.getLocalBounds().width / 2;
    float textY2 = window.getSize().y / 2 - losingText.getLocalBounds().height;
    losingText.setPosition(sf::Vector2f(textX2, textY2));


    const sf::Time framesPerSec = sf::seconds(0.07f);
    sf::Time totalTime = sf::Time::Zero;
    sf::Clock clock;
    while (window.isOpen())
    {

        totalTime += clock.restart();
        if (totalTime > framesPerSec)
        {
            totalTime -= framesPerSec;

            window.clear();
            renderer.render();
            if (game.getWinStatus())
            {
                // won
                window.draw(winningText);
            }

            if (!game.canMove())
            {
                // lost
                window.draw(losingText);
            }

            game.eventProcess();

            window.display();
        }
    }
}