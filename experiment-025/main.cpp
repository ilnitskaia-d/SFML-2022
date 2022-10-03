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

    class Player
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
        Player(Game &game)
            : mGame(game)
        {
            shape.setFillColor(sf::Color::Cyan);
            shape.setSize(sf::Vector2f(100, 100));
        }

        void setPos(size_t r, size_t c)
        {
            mR = r;
            mC = c;

            mX = 100 * c;
            mY = 100 * r;

            shape.setPosition(mX, mY);

            rect = sf::FloatRect(shape.getPosition(), shape.getSize());
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(shape);
        }

        void setDir()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                mDir.x = -1;
                mDir.y = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                mDir.x = 1;
                mDir.y = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                mDir.x = 0;
                mDir.y = -1;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                mDir.x = 0;
                mDir.y = 1;
            }
            else
            {
                mDir.x = 0;
                mDir.y = 0;
            }
        }

        void move()
        {
            rect.left += mDir.x;
            rect.top += mDir.y;

            mC = (rect.left + 1) / 100;
            mR = (rect.top + 1) / 100;

            bool canMove = true;
            for (auto const &v : mGame.mGameObjects)
            {
                for (auto const &p : v)
                {
                    if (p)
                    {
                        if (rect.intersects(p->getRect()))
                        {
                            canMove = false;
                        }
                    }
                }
            }

            if (canMove)
            {
                shape.move(mDir);
            }
            else
            {
                rect.left -= mDir.x;
                rect.top -= mDir.y;
                mC = (rect.left + 1) / 100;
                mR = (rect.top + 1) / 100;
            }
            for (const auto &e : mGame.mEnemy)
            {
                if (rect.intersects(e->getRect()))
                {
                    shape.setFillColor(sf::Color::Green);
                }
            }
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
        Enemy(Game &game, size_t r, size_t c)
            : mGame(game), mR(r), mC(c)
        {
            shape.setFillColor(sf::Color::Red);
            shape.setSize(sf::Vector2f(100, 100));

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

        sf::FloatRect getRect()
        {
            return rect;
        }

        void move()
        {
            rect.left += mDir.x;
            rect.top += mDir.y;

            mC = (rect.left + 1) / 100;
            mR = (rect.top + 1) / 100;

            if (mGame.mGameObjects[mR + mDir.y][mC + mDir.x])
            {
                if (rect.intersects(mGame.mGameObjects[mR + mDir.y][mC + mDir.x]->getRect()))
                {
                    rect.left -= mDir.x;
                    rect.top -= mDir.y;
                    mC = (rect.left + 1) / 100;
                    mR = (rect.top + 1) / 100;
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
    vector<unique_ptr<Enemy>> mEnemy;
    Player mPlayer;
    sf::RenderWindow window;

public:
    Game()
        : mPlayer(*this), window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen)
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
                    mEnemy.push_back(make_unique<Enemy>(*this, r, c));
                    mGameObjects[r].push_back(nullptr);
                }
                else if (mLevels[level][r][c] == 'P')
                {
                    mPlayer.setPos(r, c);
                    mGameObjects[r].push_back(nullptr);
                }
                else
                {
                    mGameObjects[r].push_back(nullptr);
                }
            }
        }
        for (auto const &e : mEnemy)
        {
            e->setDir();
        }
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
                else
                {
                    mPlayer.setDir();
                    mPlayer.move();
                }
            }

            for (const auto &e : mEnemy)
            {
                e->move();
            }

            window.clear();
            for (const auto &v : mGameObjects)
            {
                for (const auto &p : v)
                {
                    if (p)
                    {
                        {
                            p->draw(window);
                        }
                    }
                }
            }

            for (const auto &e : mEnemy)
            {
                e->draw(window);
            }

            mPlayer.draw(window);

            window.display();
        }
    }
};

int main()
{
    Game game;
    game.run();
}