#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "..\libs\random.hpp"

#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>

using namespace std;
using Random = effolkronium::random_static;

class Game
{
    class GameObject
    {
        Game &mGame;
        float mX;
        float mY;
        size_t mR;
        size_t mC;
        sf::RectangleShape shape;
        sf::FloatRect rect;

    public:
        GameObject(Game &game, size_t r, size_t c)
            : mGame(game)
        {
            mX = 100 * c;
            mY = 100 * r;
            shape.setFillColor(sf::Color::White);
            shape.setPosition(mX, mY);
            shape.setSize(sf::Vector2f(100, 100));

            rect = sf::FloatRect(shape.getPosition(), shape.getSize());
        }

        sf::FloatRect getRect()
        {
            return rect;
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(shape);
        }
    };

    class Enemy
    {
        Game &mGame;
        float mX;
        float mY;
        size_t mR;
        size_t mC;
        sf::RectangleShape shape;
        sf::Vector2f mDir;
        sf::FloatRect rect;

    public:
        Enemy(Game &game)
            : mGame(game)
        {
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(mX, mY);
            shape.setSize(sf::Vector2f(100, 100));
        }

        void setPos(int r, int c)
        {
            mR = r;
            mC = c;

            mX = 100 * c;
            mY = 100 * r;

            shape.setPosition(mX, mY);

            rect = sf::FloatRect(shape.getPosition(), shape.getSize());
        }

        void setDir()
        {
            vector<sf::Vector2f> posDirs;
            vector<int> dRow = {-1, 0, 1, 0};
            vector<int> dCol = {0, 1, 0, -1};

            for (int i = 0; i < 4; i++)
            {
                int tR = mR + dRow[i];
                int tC = mC + dCol[i];

                if (!mGame.mGameObjects[tR][tC])
                {
                    posDirs.emplace_back(dCol[i], dRow[i]);
                }
            }

            int n = Random::get(0, int(posDirs.size() - 1));

            mDir = posDirs[n];
            shape.move(mDir);
        }

        void move()
        {
            rect.left += mDir.x;
            rect.top += mDir.y;

            mC = shape.getPosition().x / 100;
            mR = shape.getPosition().y / 100;

            if (mGame.mGameObjects[mR + mDir.y][mC + mDir.x])
            {
                if (rect.intersects(mGame.mGameObjects[mR + mDir.y][mC + mDir.x]->getRect()))
                {
                    rect.left -= mDir.x;
                    rect.top -= mDir.y;
                    setDir();
                }
                else
                {
                    shape.move(mDir);
                }
            }
            else
            {
                shape.move(mDir);
            }
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(shape);
        }
    };

    vector<vector<unique_ptr<GameObject>>> mGameObjects;
    vector<vector<string>> mLevels;
    Enemy enemy;
    sf::RenderWindow window;

public:
    Game()
        : enemy(*this), window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen)
    {
        loadLevels();
        loadTiles(0);
    }

    bool loadLevels()
    {
        fstream level("data/levels.data");
        if (!level)
        {
            cout << "file not found" << endl;
            return false;
        }
        for (;;)
        {
            string line;
            if (!getline(level, line))
            {
                break;
            }

            if (!getline(level, line))
            {
                return false;
            }

            int h;
            istringstream sinp(line);
            if (!(sinp >> h))
            {
                return false;
            }

            vector<string> curLevel;
            for (int i = 0; i < int(h); i++)
            {
                if (!getline(level, line))
                {
                    return false;
                }
                curLevel.push_back(line);
            }

            mLevels.push_back(curLevel);
        }

        return true;
    }

    void loadTiles(size_t level)
    {

        mGameObjects.resize(mLevels[level].size());

        for (size_t r = 0; r < mLevels[level].size(); r++)
        {
            for (size_t c = 0; c < mLevels[level][r].size(); c++)
            {
                if (mLevels[level][r][c] == 'W')
                {
                    mGameObjects[r].push_back(make_unique<GameObject>(*this, r, c));
                }
                else if (mLevels[level][r][c] == 'E')
                {
                    enemy.setPos(r, c);
                    mGameObjects[r].push_back(nullptr);
                }
                else
                {
                    // mGameObjects[r].push_back(make_unique<GameObject>(*this, r, c, false));
                    mGameObjects[r].push_back(nullptr);
                }
            }
        }
        enemy.setDir();
    }

    void run()
    {

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            enemy.move();
            window.clear();
            for (const auto &v : mGameObjects)
            {
                for (const auto &p : v)
                {
                    if (p)
                    {
                        if (p->isWall())
                        {
                            p->draw(window);
                        }
                    }
                }
            }

            enemy.draw(window);
            window.display();
        }
    }
};

int main()
{
    Game game;
    game.run();
}