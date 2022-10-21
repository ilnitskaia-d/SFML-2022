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
    public:
        Game &mGame;
        int mX;
        int mY;
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

        virtual void draw(sf::RenderWindow &window)
        {
            window.draw(shape);
        }
    };

    class Explosion : public GameObject
    {
        int mCounter;
        int mFrameIndex;
        size_t mR;
        size_t mC;
        int mX;
        int mY;
        sf::Texture mTexture;
        vector<unique_ptr<sf::Sprite>> mSprites;
        sf::FloatRect mRect;

    public:
        Explosion(Game &game, size_t r, size_t c)
            : GameObject(game, r, c), mCounter(0), mFrameIndex(0), mR(r), mC(c)
        {
            if (!mTexture.loadFromFile("data/explosion.png"))
            {
                std::cout << "failed to load from file" << std::endl;
                exit(1);
            }

            int frameW = mTexture.getSize().x / 4;

            for (int j = 0; j < 4; ++j)
            {
                mSprites.push_back(make_unique<sf::Sprite>(mTexture, sf::IntRect(j * frameW, 0, frameW, 32)));
                mSprites.back()->setScale(3, 3);
                mSprites.back()->setPosition(mC * 100, mR * 100);
            }

            // mX = mC * mSprites[mFrameIndex]->getGlobalBounds().width;
            // mY = mR * mSprites[mFrameIndex]->getGlobalBounds().height;
        }

        sf::FloatRect getSprite() const
        {
            return mSprites.back()->getGlobalBounds();
        }

        void draw(sf::RenderWindow &window) override
        {
            // mSprites[mFrameIndex]->setOrigin(mSprites[mFrameIndex]->getLocalBounds().width / 2.0f,
            //                                  mSprites[mFrameIndex]->getLocalBounds().height / 2.0f);

            auto p = dynamic_cast<Explosion *>(mGame.mGameObjects[mR][mC].get());
            for (auto &e : mGame.mEnemy)
            {
                if (e)
                {
                    if (e->getRect().intersects(p->getSprite()))
                    {
                        e->kill();
                        e.release();
                    }
                }
            }

            window.draw(*mSprites[mFrameIndex]);
            ++mCounter;
            if (mCounter == 20)
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1);
                if (mFrameIndex == (int)mSprites.size())
                {
                    mGame.mGameObjects[mR][mC].release();
                }
            }
        }
    };

    class Bomb : public GameObject
    {
        int mCounter;
        int mFrameIndex;
        int mR;
        int mC;
        sf::Texture mTexture;
        vector<unique_ptr<sf::Sprite>> mSprites;

    public:
        Bomb(Game &game, size_t r, size_t c)
            : GameObject(game, r, c), mCounter(0), mFrameIndex(0), mR(r), mC(c)
        {
            if (!mTexture.loadFromFile("data/bomb.png"))
            {
                std::cout << "failed to load from file" << std::endl;
                exit(1);
            }

            int frameW = mTexture.getSize().x / 6;

            for (int j = 0; j < 6; ++j)
            {
                mSprites.push_back(make_unique<sf::Sprite>(mTexture, sf::IntRect(j * frameW, 0, frameW, 32)));
                mSprites.back()->setScale(3, 3);
                mSprites.back()->setPosition(mC * 100, mR * 100);
            }
        }

        void draw(sf::RenderWindow &window) override
        {

            window.draw(*mSprites[mFrameIndex]);
            ++mCounter;
            if (mCounter == 30)
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1);
                if (mFrameIndex == (int)mSprites.size())
                {
                    mGame.setExplosion(mR, mC, 2);
                    mGame.mGameObjects[mR][mC].release();
                }
            }
        }
    };

    class Player
    {
        Game &mGame;
        int mX;
        int mY;
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                mGame.setBomb((size_t)((shape.getPosition().y + shape.getSize().y / 2) / shape.getSize().y) + mDir.y,
                              (size_t)((shape.getPosition().x + shape.getSize().x / 2) / shape.getSize().x) + mDir.x);
            }
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
                        auto pB = dynamic_cast<Bomb *>(p.get());
                        auto pE = dynamic_cast<Explosion *>(p.get());
                        if (pB == nullptr && pE == nullptr)
                        {
                            if (rect.intersects(p->getRect()))
                            {
                                canMove = false;
                            }
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
                if (e)
                {
                    if (rect.intersects(e->getRect()))
                    {
                        shape.setFillColor(sf::Color::Green);
                    }
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
        bool isKilled;

    public:
        Enemy(Game &game, size_t r, size_t c)
            : mGame(game), mR(r), mC(c), isKilled(false)
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

                auto p = dynamic_cast<Explosion *>(mGame.mGameObjects[tR][tC].get());
                auto p1 = dynamic_cast<Bomb *>(mGame.mGameObjects[tR][tC].get());
                if (!mGame.mGameObjects[tR][tC] || p != nullptr || p1 != nullptr)
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

        void kill()
        {
            isKilled = true;
        }

        void move()
        {
            rect.left += mDir.x;
            rect.top += mDir.y;

            mC = (rect.left + 1) / 100;
            mR = (rect.top + 1) / 100;

            auto p = dynamic_cast<Explosion *>(mGame.mGameObjects[mR + mDir.y][mC + mDir.x].get());
            auto p1 = dynamic_cast<Bomb *>(mGame.mGameObjects[mR + mDir.y][mC + mDir.x].get());

            if (mGame.mGameObjects[mR + mDir.y][mC + mDir.x])
            {
                if (p == nullptr && p1 == nullptr)
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

    void setBomb(size_t r, size_t c)
    {
        mGameObjects[r][c].reset(new Bomb(*this, r, c));
    }

    void setExplosion(size_t r, size_t c, int length)
    {
        vector<int> dRow = {-1, 0, 1, 0};
        vector<int> dCol = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i)
        {
            int tR = r;
            int tC = c;
            for (int j = 0; j < length; ++j)
            {
                if (mGameObjects[tR + dRow[i]][tC + dCol[i]])
                {
                    break;
                }
                mGameObjects[tR + dRow[i]][tC + dCol[i]].reset(new Explosion(*this, tR + dRow[i], tC + dCol[i]));

                tR += dRow[i];
                tC += dCol[i];
            }
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
                if (e)
                {
                    e->move();
                }
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
                if (e)
                {
                    e->draw(window);
                }
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