#include <fstream>
#include <sstream>
#include <iostream>
#include "Game.hpp"
#include "MainCharacter.hpp"

using namespace std;

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mField(mWindow),
      mCharacter(mWindow, mWindow.getSize().x / 2.0f, mWindow.getSize().y / 2.0f)
{
    mWindow.setVerticalSyncEnabled(true);

    if (!loadLevels())
    {
        cout << "can't read from file" << endl;
        exit(1);
    }
    loadTiles(0);
}

bool Game::loadLevels()
{
    fstream level("data/levels.data");
    if (!level)
    {
        cout << "file not found" << endl;
        return false;
    }

    string line;
    if (!getline(level, line))
    {
        cout << "line" << endl;
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
    return true;
}

void Game::loadTiles(size_t level)
{
    mGameObjects.resize(mLevels[level].size());
    for (size_t j = 0; j < mLevels[level].size(); j++)
    {
        for (size_t i = 0; i < mLevels[level][j].size(); i++)
        {
            if (mLevels[level][j][i] == 'A')
            {
                mGameObjects[j].push_back(make_unique<Apple>(*this, "data/apple.png", j, i));
            }
            else if (mLevels[level][j][i] == 'F')
            {
                mGameObjects[j].push_back(make_unique<Flower>(*this, "data/flower.png", j, i));
            }
            // else if (mLevels[level][j][i] == 'B')
            // {
            //     mGameObjects[j].push_back(make_unique<Ball>(*this, "data/ball.png", j, i));
            // }
        }
    }
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
        for (const auto &v : mGameObjects)
        {
            for (const auto &p : v)
            {
                p->draw();
                p->info();
            }
        }
        mCharacter.draw();
        mWindow.display();
    }
}

Game::GameObject::GameObject(Game &game, const string &path, int r, int c)
    : mGame(game), mRow(r), mCol(c)
{
    mTexture.loadFromFile(path);
    mSprite.setTexture(mTexture);
    mSprite.setScale(4, 4);
    // mSprite.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
    mX = mSprite.getGlobalBounds().width * r;
    mY = mSprite.getGlobalBounds().height * c;
    mSprite.setPosition(sf::Vector2f(mX, mY));
}

Game::Flower::Flower(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Flower::draw()
{
    mSprite.setPosition(sf::Vector2f(mX, mY));
    mGame.mWindow.draw(mSprite);
}

Game::Apple::Apple(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Apple::draw()
{
    mSprite.setPosition(sf::Vector2f(mX, mY));
    mGame.mWindow.draw(mSprite);
}

bool Game::Apple::move(int dx, int dy)
{
    mX += dx;
    mY += dy;
    return true;
}

Game::Ball::Ball(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Ball::draw()
{
    mGame.mWindow.draw(mSprite);
}

bool Game::Ball::move(int dx, int dy)
{
    mX += dx;
    mY += dy;
    return true;
}