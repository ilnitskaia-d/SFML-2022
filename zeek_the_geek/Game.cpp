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

    mCellSize = mGameObjects[0][0]->getSize();
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
    for (size_t r = 0; r < mLevels[level].size(); r++)
    {
        for (size_t c = 0; c < mLevels[level][r].size(); c++)
        {
            if (mLevels[level][r][c] == 'A')
            {
                mGameObjects[r].push_back(make_unique<Apple>(*this, "data/apple.png", r, c));
            }
            else if (mLevels[level][r][c] == 'F')
            {
                mGameObjects[r].push_back(make_unique<Flower>(*this, "data/flower.png", r, c));
            }
            else if (mLevels[level][r][c] == 'W')
            {
                mGameObjects[r].push_back(make_unique<Wall>(*this, "data/wall_0.png", r, c));
            }
            else if (mLevels[level][r][c] == 'B')
            {
                mGameObjects[r].push_back(make_unique<Ball>(*this, "data/ball.png", r, c));
            }
            else if (mLevels[level][r][c] == 'C')
            {
                mGameObjects[r].push_back(nullptr);
                mCharacter.setCoords(r, c);
                mLevels[level][r][c] = '.';
            }
            else
            {
                mGameObjects[r].push_back(nullptr);
            }
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
        }

        mWindow.clear();
        for (const auto &v : mGameObjects)
        {
            for (const auto &p : v)
            {
                if (p)
                {
                    p->draw();
                }
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
    mX = (game.mWindow.getSize().x / 2.0f - mSprite.getGlobalBounds().width * (game.mLevels[0][0].size() / 2.0f)) + mSprite.getGlobalBounds().width * c;
    mY = (game.mWindow.getSize().y / 2.0f - mSprite.getGlobalBounds().height * (game.mLevels[0].size() / 2.0f)) + mSprite.getGlobalBounds().height * r;
    mSprite.setPosition(sf::Vector2f(mX, mY));
}

Game::IMovable::IMovable()
    : curState(State::Standing), mDirection(0, 0)
{
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
    move();
}

void Game::Apple::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    mGame.mGameObjects[mRow + dr][mCol + dc].swap(mGame.mGameObjects[mRow][mCol]);
    swap(mGame.mLevels[0][mRow + dr][mCol + dc], mGame.mLevels[0][mRow][mCol]);

    mDirection.x = distOfStep * dc;
    mDirection.y = distOfStep * dr;
    mRow += dr;
    mCol += dc;
    curState = State::Moving;
}

bool Game::Apple::move()
{
    if (curState == State::Moving)
    {
        mX += mDirection.x;
        mY += mDirection.y;
        --mNumOfSteps;
        if (mNumOfSteps == 0)
        {
            mDirection.x = 0;
            mDirection.y = 0;
            curState = State::Standing;
        }
        mSprite.setPosition(mX, mY);
    }
    return true;
}

Game::Ball::Ball(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Ball::draw()
{
    mGame.mWindow.draw(mSprite);
    move();
}

void Game::Ball::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    mGame.mGameObjects[mRow + dr][mCol + dc].swap(mGame.mGameObjects[mRow][mCol]);
    swap(mGame.mLevels[0][mRow + dr][mCol + dc], mGame.mLevels[0][mRow][mCol]);

    mDirection.x = distOfStep * dc;
    mDirection.y = distOfStep * dr;
    mRow += dr;
    mCol += dc;
    curState = State::Moving;
}

bool Game::Ball::move()
{
    if (curState == State::Moving)
    {
        mX += mDirection.x;
        mY += mDirection.y;
        --mNumOfSteps;
        if (mNumOfSteps == 0)
        {
            mDirection.x = 0;
            mDirection.y = 0;
            curState = State::Standing;
        }
        mSprite.setPosition(mX, mY);
    }
    return true;
}

// MainCharacter
Game::MainCharacter::MainCharacter(Game &game)
    : mGame(game),
      mCounter(0), mAnimationIndex(0), mFrameIndex(0), curState(State::Standing), mDirection(sf::Vector2f(0.0f, 0.0f)),
      mNumOfSteps(MaxCount * 4), mDistOfSteps(32 * 4 / mNumOfSteps)
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
    mRow = row;
    mCol = col;
    float x = (mGame.mWindow.getSize().x / 2.0f - mSprites[0][0]->getGlobalBounds().width * (mGame.mLevels[0][0].size() / 2.0f)) + mSprites[0][0]->getGlobalBounds().width * col;
    float y = (mGame.mWindow.getSize().y / 2.0f - mSprites[0][0]->getGlobalBounds().width * (mGame.mLevels[0].size() / 2.0f)) + mSprites[0][0]->getGlobalBounds().width * row;
    mCoords = sf::Vector2f(x, y);
}

void Game::MainCharacter::draw()
{
    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f, mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mCoords);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (curState == State::Moving)
    {
        ++mCounter;
        if (mCounter == MaxCount)
        {
            mCounter = 0;
            mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
        }
    }
    move();
}

bool Game::MainCharacter::canMove(int dr, int dc) const
{
    if (mGame.mLevels[0][mRow + dr][mCol + dc] == '.')
    {
        return true;
    }

    if (mGame.mLevels[0][mRow + dr][mCol + dc] == 'A' && mGame.mLevels[0][mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Apple *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mLevels[0][mRow + dr][mCol + dc] == 'B' && mGame.mLevels[0][mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Ball *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    return false;
}

void Game::MainCharacter::move()
{
    if (curState == State::Moving)
    {
        mCoords += mDirection;
        --mNumOfSteps;
        if (mNumOfSteps == 0)
        {
            curState = State::Standing;
            mFrameIndex = 0;
            mDirection.x = 0;
            mDirection.y = 0;
        }
    }
    else
    {
        mNumOfSteps = MaxCount * 4;
        float distOfStep = mGame.mCellSize / mNumOfSteps;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && canMove(0, -1))
        {
            curState = State::Moving;
            mDirection.x = -distOfStep;
            mDirection.y = 0;
            mAnimationIndex = 1;
            mFrameIndex = 0;
            --mCol;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && canMove(0, 1))
        {
            curState = State::Moving;
            mDirection.x = distOfStep;
            mDirection.y = 0;
            mAnimationIndex = 2;
            mFrameIndex = 0;
            ++mCol;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canMove(-1, 0))
        {
            curState = State::Moving;
            mDirection.x = 0;
            mDirection.y = -distOfStep;
            mAnimationIndex = 3;
            mFrameIndex = 0;
            --mRow;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && canMove(1, 0))
        {
            curState = State::Moving;
            mDirection.x = 0;
            mDirection.y = distOfStep;
            mAnimationIndex = 0;
            mFrameIndex = 0;
            ++mRow;
        }
    }
}
