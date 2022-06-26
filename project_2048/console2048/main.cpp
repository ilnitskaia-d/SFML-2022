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

    cout << goal << endl;

    Game2048 game;
    Renderer renderer(game);
    renderer.render();
    cout << "cmd> ";

    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "left")
        {
            game.moveLeft();
        }
        else if (cmd == "right")
        {
            game.moveRight();
        }
        else if (cmd == "up")
        {
            game.moveUp();
        }
        else if (cmd == "down")
        {
            game.moveDown();
        }
        else if (cmd == "exit")
        {
            break;
        }
        else
        {
            cout << "unknown command try : left, right, up, down, exit.\n";
            continue;
        }
        renderer.render();
        if(game.getWinStatus())
        {
            cout << "congrats!!!\n";
            break;
        }
        cout << "cmd> ";
    }
}