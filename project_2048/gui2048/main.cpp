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

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    Game2048 game(window, goal);
    Renderer renderer(game, window);
    window.setVerticalSyncEnabled(true);
    renderer.render();

    const sf::Time framesPerSec = sf::seconds(0.1f);
    sf::Time totalTime = sf::Time::Zero;
    sf::Clock clock;
    while (window.isOpen())
    {
        totalTime += clock.restart();
        if (totalTime > framesPerSec)
        {
            totalTime -= framesPerSec;
            // update();
            game.eventProcess();
            window.clear();
            renderer.render();
            window.display();
        }

        if (game.getWinStatus())
        {
            cout << "Congratulations!!!\n";
            break;
        }

        if (!game.canMove())
        {
            cout << "Game lost";
            break;
        }
    }
}