#include "Field.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Field::Field(sf::RenderWindow &window)
    : mWindow(window), curLevelIndex(0)
{
    if (!loadLevels())
    {
        cout << "failed to load levels" << endl;
        exit(1);
    }

    if (!mFloorTexture.loadFromFile("data/floor_0.png"))
    {
        cout << "failed to load texture of floor" << endl;
    }

    if (!mWallTexture.loadFromFile("data/wall_0.png"))
    {
        cout << "failed to load texture of floor" << endl;
    }

    loadTiles(curLevelIndex);
}

bool Field::loadLevels()
{
    fstream level("data/levels.data");
    if (!level)
    {
        cout << "file not found" << endl;
        return false;
    }

    // for (;;)
    {
        string line;
        if (!getline(level, line))
        {
            cout << line << endl;
            return false;
        }

        int h;
        istringstream sinp(line);
        if (!(sinp >> h))
        {
            cout << "error 2" << endl;
            return false;
        }

        vector<string> curLevel;
        for (int i = 0; i < int(h); i++)
        {
            if (!getline(level, line))
            {
                cout << "error 3" << endl;
                return false;
            }
            curLevel.push_back(line);
        }

        mLevels.push_back(curLevel);
    }

    return true;
}

void Field::loadTiles(size_t level)
{
    for (size_t j = 0; j < mLevels[level].size(); j++)
    {
        for (size_t i = 0; i < mLevels[level][j].size(); i++)
        {
            if (mLevels[level][j][i] == '#')
            {
                mField.push_back(make_unique<sf::Sprite>(mWallTexture));
            }
            else
            {
                mField.push_back(make_unique<sf::Sprite>(mFloorTexture));
            }
            mField.back()->scale(6, 6);
            mField.back()->setPosition(sf::Vector2f(i * mField.back()->getGlobalBounds().height, j * mField.back()->getGlobalBounds().height));
        }
    }
}

void Field::draw()
{
    for (auto &p : mField)
    {
        mWindow.draw(*p);
    }
}
