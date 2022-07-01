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

    Game2048 game(goal);
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    Renderer renderer(game, window);
    window.setVerticalSyncEnabled(true);
    renderer.render();

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    game.moveLeft();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    game.moveRight();
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    game.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    game.moveDown();
                }
            }
            window.clear();
            // renderer.renderFrames(window);
            renderer.render();

            window.display();
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
}