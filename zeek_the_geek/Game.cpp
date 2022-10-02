#include <fstream>
#include <sstream>
#include <iostream>
#include "Game.hpp"

using namespace std;

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mCharacter(*this), mScore(0), mCurLevel(0)
{
    mWindow.setVerticalSyncEnabled(true);
    mFloorText.loadFromFile("data/floor_0.png");
    mFloorSprite.setTexture(mFloorText);

    if (!loadLevels())
    {
        cout << "can't read from file" << endl;
        exit(1);
    }

    loadTiles(0);
    mFloorSprite.setScale(mScale, mScale);
    mFloorSprite.setOrigin(mFloorSprite.getLocalBounds().width / 2, mFloorSprite.getLocalBounds().height / 2);

    mFont.loadFromFile("data/FONT.TTF");
    mScoreBar.setFont(mFont);
    mScoreBar.setCharacterSize(mCellSize / 2);
    mScoreBar.setFillColor(sf::Color::White);
    mScoreBar.setPosition(0, 0);
}

void Game::prepareNextLevel()
{
    if (mCurLevel < mLevels.size() - 1)
    {
        mCurLevel++;
        loadTiles(mCurLevel);
    }
}

bool Game::loadLevels()
{
    std::fstream level("data/levels.data");
    if (!level)
    {
        std::cout << "file not found" << std::endl;
        return false;
    }
    for (;;)
    {
        std::string line;
        if (!std::getline(level, line))
        {
            break;
        }

        if (!std::getline(level, line))
        {
            cout << "1 problem" << endl;
            return false;
        }

        int h;
        std::istringstream sinp(line);
        if (!(sinp >> h))
        {
            cout << "2 problem" << endl;
            return false;
        }

        std::vector<std::string> curLevel;
        for (int i = 0; i < int(h); i++)
        {
            if (!std::getline(level, line))
            {
                cout << "3 problem" << endl;
                return false;
            }
            curLevel.push_back(line);
        }

        mLevels.push_back(curLevel);
    }

    return true;
}

void Game::loadTiles(size_t level)
{

    mCurMap = mLevels[level];

    if (mWindow.getSize().y / mCurMap.size() < mWindow.getSize().x / mCurMap[0].size())
    {
        mScale = (float)mWindow.getSize().y / ((float)mCurMap.size() * 32.0f);
        cout << mWindow.getSize().y << endl;
        cout << mCurMap.size() << endl;
    }
    else
    {
        mScale = (float)mWindow.getSize().x / ((float)mCurMap[0].size() * 32.0f);
        cout << mWindow.getSize().x << endl;
        cout << mCurMap[0].size() << endl;
    }

    mCellSize = mFloorSprite.getLocalBounds().height * mScale;

    mCenterX = mWindow.getSize().x / 2.0f - mCellSize * (mLevels[mCurLevel][0].size() / 2.0f);
    mCenterY = mWindow.getSize().y / 2.0f - mCellSize * (mLevels[mCurLevel].size() / 2.0f);

    mGameObjects.clear();
    mGameObjects.resize(mCurMap.size());
    for (size_t r = 0; r < mCurMap.size(); r++)
    {
        for (size_t c = 0; c < mCurMap[r].size(); c++)
        {
            if (mCurMap[r][c] == 'A')
            {
                mGameObjects[r].push_back(make_unique<Apple>(*this, "data/apple.png", r, c));
            }
            else if (mCurMap[r][c] == 'F')
            {
                mGameObjects[r].push_back(make_unique<Flower>(*this, "data/flower.png", r, c));
            }
            else if (mCurMap[r][c] == 'W')
            {
                mGameObjects[r].push_back(make_unique<Wall>(*this, "data/wall_0.png", r, c));
            }
            else if (mCurMap[r][c] == 'B')
            {
                mGameObjects[r].push_back(make_unique<Ball>(*this, "data/ball.png", r, c));
            }
            else if (mCurMap[r][c] == 'M')
            {
                mGameObjects[r].push_back(make_unique<Mouse>(*this, "data/mouse.png", r, c));
            }
            else if (mCurMap[r][c] == 'E')
            {
                mGameObjects[r].push_back(make_unique<Bomb>(*this, "data/bomb.png", r, c));
            }
            else if (mCurMap[r][c] == 'R')
            {
                mGameObjects[r].push_back(make_unique<BadCat>(*this, "data/badcat.png", r, c));
            }
            else if (mCurMap[r][c] == 'K')
            {
                mGameObjects[r].push_back(make_unique<Key>(*this, "data/key.png", r, c));
            }
            else if (mCurMap[r][c] == 'D')
            {
                mGameObjects[r].push_back(make_unique<Door>(*this, "data/door.png", r, c));
            }
            else if (mCurMap[r][c] == 'S')
            {
                mGameObjects[r].push_back(make_unique<Snake>(*this, "data/snake.png", r, c));
            }
            else if (mCurMap[r][c] == 'C')
            {
                mGameObjects[r].push_back(nullptr);
                mCharacter.setCoords(r, c);
                mCharacter.reset();
                mCurMap[r][c] = '.';
            }
            else
            {
                mGameObjects[r].push_back(nullptr);
            }
        }
    }
}

void Game::drawField()
{
    for (size_t r = 0; r < mLevels[mCurLevel].size(); r++)
    {
        for (size_t c = 0; c < mLevels[mCurLevel][r].size(); c++)
        {
            mFloorSprite.setPosition(mCenterX + mCellSize * c, mCenterY + mCellSize * r);
            mWindow.draw(mFloorSprite);
        }
    }
}

void Game::restart()
{
    loadTiles(mCurLevel);
    mCharacter.setCaught(false);
    mCharacter.setKey(false);
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
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                restart();
            }
        }

        mWindow.clear();
        drawField();
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

        mScoreBar.setString("Score: " + to_string(mScore));
        mWindow.draw(mScoreBar);

        mWindow.display();
    }
}

Game::GameObject::GameObject(Game &game, const string &path, int r, int c)
    : mGame(game), mRow(r), mCol(c),
      curState(State::Standing), mDirection(0, 0),
      mCounter(0), mAnimationIndex(0), mFrameIndex(0)
{
    mTexture.loadFromFile(path);

    int nFramesX = mTexture.getSize().x / 32;
    int nFramesY = mTexture.getSize().y / 32;

    int frameSize = 32;

    mSprites.resize(nFramesY);
    for (int i = 0; i < nFramesY; ++i)
    {
        for (int j = 0; j < nFramesX; ++j)
        {
            mSprites[i].push_back(make_unique<sf::Sprite>(mTexture, sf::IntRect(j * frameSize, i * frameSize, frameSize, frameSize)));
            mSprites[i].back()->setScale(mGame.mScale, mGame.mScale);
        }
    }

    mSprites[0][0]->setOrigin(frameSize / 2.0f, frameSize / 2.0f);
    mX = mGame.mCenterX + frameSize * 4 * c;
    mY = mGame.mCenterY + frameSize * 4 * r;
    mSprites[0][0]->setPosition(sf::Vector2f(mX, mY));
}

Game::Wall::Wall(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Wall::draw()
{
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
}

Game::Mouse::Mouse(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Mouse::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Mouse::activate()
{
    mGame.mCurMap[mRow][mCol] = '.';
    mGame.mGameObjects[mRow][mCol].release();
    mActivated = true;
    mGame.prepareNextLevel();
}
