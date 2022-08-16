#include <fstream>
#include <sstream>
#include <iostream>
#include "Game.hpp"
// #include "MainCharacter.hpp"

using namespace std;

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mCharacter(*this)
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
                mGameObjects[j].push_back(make_unique<Apple>(*this, "data/apple.png", i, j));
            }
            else if (mLevels[level][j][i] == 'F')
            {
                mGameObjects[j].push_back(make_unique<Flower>(*this, "data/flower.png", i, j));
            }
            else if (mLevels[level][j][i] == 'W')
            {
                mGameObjects[j].push_back(make_unique<Flower>(*this, "data/wall_0.png", i, j));
            }
            else if (mLevels[level][j][i] == 'C')
            {
                mCharacter.setCoords(i, j);
            }
            else
            {
                mGameObjects[j].push_back(make_unique<Floor>(*this, "data/floor_0.png", i, j));
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
        // mField.draw();
        for (const auto &v : mGameObjects)
        {
            for (const auto &p : v)
            {
                p->draw();
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
    mSprite.setOrigin(mSprite.getLocalBounds().width / 2.0f, mSprite.getLocalBounds().height / 2.0f);
    mX = (game.mWindow.getSize().x / 2.0f - mSprite.getGlobalBounds().width * (game.mLevels[0][0].size() / 2.0f)) + mSprite.getGlobalBounds().width * r;
    mY = (game.mWindow.getSize().y / 2.0f - mSprite.getGlobalBounds().height * (game.mLevels[0].size() / 2.0f)) + mSprite.getGlobalBounds().height * c;
    mSprite.setPosition(sf::Vector2f(mX, mY));
}

Game::Floor::Floor(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Floor::draw()
{
    mGame.mWindow.draw(mSprite);
}

Game::Wall::Wall(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Wall::draw()
{
    mGame.mWindow.draw(mSprite);
}

Game::Flower::Flower(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Flower::draw()
{
    mGame.mWindow.draw(mSprite);
}

Game::Apple::Apple(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Apple::draw()
{
    mGame.mWindow.draw(mSprite);
}

bool Game::Apple::checkTiles(float x, float y)
{   
    return true;
}

bool Game::Apple::move(int dx, int dy)
{
    mX += dx;
    mY += dy;
    mSprite.setPosition(mX, mY);
    mRow = (mX - (mGame.mWindow.getSize().x / 2.0f - mSprite.getGlobalBounds().width * (mGame.mLevels[0][0].size() / 2.0f))) / mSprite.getGlobalBounds().width;
    mCol = (mY - (mGame.mWindow.getSize().y / 2.0f - mSprite.getGlobalBounds().height * (mGame.mLevels[0].size() / 2.0f))) / mSprite.getGlobalBounds().height;
    cout << mRow << " " << mCol << endl;
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

bool Game::Ball::checkTiles(float x, float y)
{
    x /= 5;
    y /= 5;
    return mGame.mLevels[0][mRow + y][mCol + x] == '.';
}

bool Game::Ball::move(int dx, int dy)
{
    mX += dx;
    mY += dy;
    mSprite.setPosition(mX, mY);
    mRow = (mX - (mGame.mWindow.getSize().x / 2.0f - mSprite.getGlobalBounds().width * (mGame.mLevels[0][0].size() / 2.0f))) / mSprite.getGlobalBounds().width;
    return true;
}

// MainCharacter
Game::MainCharacter::MainCharacter(Game &game)
    : mGame(game),
      mCounter(0), mAnimationIndex(0), mFrameIndex(0), curState(State::standDown), mDirection(sf::Vector2f(0.0f, 0.0f))
{
    if (!mTexture.loadFromFile("data/cat.png"))
    {
        std::cout << "failed to load from file" << std::endl;
        exit(1);
    }

    int frameW = mTexture.getSize().x / 4;
    int frameH = mTexture.getSize().y / 4;

    mSprites.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mSprites[i].push_back(make_unique<sf::Sprite>(mTexture, sf::IntRect(j * frameW, i * frameH, frameW, frameH)));
            mSprites[i].back()->setScale(4, 4);
        }
    }
}

void Game::MainCharacter::setCoords(int row, int col)
{
    float x = (mGame.mWindow.getSize().x / 2.0f - mSprites[0][0]->getGlobalBounds().width * (mGame.mLevels[0][0].size() / 2.0f)) + mSprites[0][0]->getGlobalBounds().width * row;
    float y = (mGame.mWindow.getSize().y / 2.0f - mSprites[0][0]->getGlobalBounds().width * (mGame.mLevels[0].size() / 2.0f)) + mSprites[0][0]->getGlobalBounds().width * col;
    mCoords = sf::Vector2f(x, y);
}

void Game::MainCharacter::draw()
{
    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f, mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mCoords);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (curState == State::goLeft || curState == State::goRight || curState == State::goUp || curState == State::goDown)
    {
        ++mCounter;
        if (mCounter == 10)
        {
            mCounter = 0;
            mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
        }
    }
}

void Game::MainCharacter::move()
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        mFrameIndex = 0;
        if (curState == State::goLeft)
        {
            curState = State::standLeft;
        }
        else if (curState == State::goRight)
        {
            curState = State::standRight;
        }
        else if (curState == State::goUp)
        {
            curState = State::standUp;
        }
        else if (curState == State::goDown)
        {
            curState = State::standDown;
        }
        return;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && curState != State::goLeft)
    {
        curState = State::goLeft;
        mDirection.x = -5;
        mDirection.y = 0;
        mAnimationIndex = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && curState != State::goRight)
    {
        curState = State::goRight;
        mDirection.x = 5;
        mDirection.y = 0;
        mAnimationIndex = 2;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && curState != State::goUp)
    {
        curState = State::goUp;
        mDirection.x = 0;
        mDirection.y = -5;
        mAnimationIndex = 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && curState != State::goDown)
    {
        curState = State::goDown;
        mDirection.x = 0;
        mDirection.y = 5;
        mAnimationIndex = 0;
    }

    bool canMove = true;
    bool movableObj = false;

    for (const auto &row : mGame.mGameObjects)
    {
        for (const auto &p : row)
        {
            if (p->cantMove(mCoords.x + mDirection.x, mCoords.y + mDirection.y, mSprites[0][0]->getGlobalBounds().width / 2.0f))
            {
                if (auto p1 = dynamic_cast<Apple *>(p.get()))
                {
                    if (p1->checkTiles(mDirection.x, mDirection.y))
                    {
                        p1->move(mDirection.x, mDirection.y);
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else if (auto p2 = dynamic_cast<Ball *>(p.get()))
                {
                    if (p2->checkTiles(mDirection.x, mDirection.y))
                    {
                        p2->move(mDirection.x, mDirection.y);
                    }
                    else
                    {
                        canMove = false;
                    }
                }
                else
                {
                    canMove = false;
                }

                break;
            }
        }
        if (!canMove || movableObj)
            break;
    }

    if (canMove || movableObj)
    {
        mCoords += mDirection;
    }
}
