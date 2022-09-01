#include <fstream>
#include <sstream>
#include <iostream>
#include "Game.hpp"

using namespace std;

Game::Game()
    : mWindow(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen), mCharacter(*this), mScore(0), mCurLevel(0)
{
    mWindow.setVerticalSyncEnabled(true);

    if (!loadLevels())
    {
        cout << "can't read from file" << endl;
        exit(1);
    }

    mFloorText.loadFromFile("data/floor_0.png");
    mFloorSprite.setTexture(mFloorText);
    mFloorSprite.setScale(4, 4);
    mFloorSprite.setOrigin(mFloorSprite.getLocalBounds().width / 2, mFloorSprite.getLocalBounds().height / 2);

    mCellSize = mFloorSprite.getGlobalBounds().width;

    loadTiles(0);

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
            return false;
        }

        int h;
        std::istringstream sinp(line);
        if (!(sinp >> h))
        {
            return false;
        }

        std::vector<std::string> curLevel;
        for (int i = 0; i < int(h); i++)
        {
            if (!std::getline(level, line))
            {
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
    mCenterX = mWindow.getSize().x / 2.0f - mCellSize * (mLevels[mCurLevel][0].size() / 2.0f);
    mCenterY = mWindow.getSize().y / 2.0f - mCellSize * (mLevels[mCurLevel].size() / 2.0f);

    mGameObjects.clear();
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
            else if (mLevels[level][r][c] == 'M')
            {
                mGameObjects[r].push_back(make_unique<Mouse>(*this, "data/mouse.png", r, c));
            }
            else if (mLevels[level][r][c] == 'E')
            {
                mGameObjects[r].push_back(make_unique<Bomb>(*this, "data/bomb.png", r, c));
            }
            else if (mLevels[level][r][c] == 'R')
            {
                mGameObjects[r].push_back(make_unique<BadCat>(*this, "data/badcat.png", r, c));
            }
            else if (mLevels[level][r][c] == 'K')
            {
                mGameObjects[r].push_back(make_unique<Key>(*this, "data/key.png", r, c));
            }
            else if (mLevels[level][r][c] == 'D')
            {
                mGameObjects[r].push_back(make_unique<Door>(*this, "data/door.png", r, c));
            }
            else if (mLevels[level][r][c] == 'S')
            {
                mGameObjects[r].push_back(make_unique<Snake>(*this, "data/snake.png", r, c));
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
            mSprites[i].back()->setScale(4, 4);
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

Game::Flower::Flower(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Flower::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Flower::activate()
{
    mGame.mLevels[mGame.mCurLevel][mRow][mCol] = '.';
    mGame.mGameObjects[mRow][mCol].release();
    mActivated = true;
    mGame.mScore++;
}

Game::Door::Door(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Door::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Door::activate()
{
    if (mGame.mCharacter.getKey())
    {
        mGame.mLevels[mGame.mCurLevel][mRow][mCol] = '.';
        // mGame.mGameObjects[mRow][mCol].release();
        mGame.mCharacter.setKey(false);
        mActivated = true;
    }
}

Game::Key::Key(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Key::draw()
{
    if (!mActivated)
    {
        mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    }
}

void Game::Key::activate()
{
    mGame.mLevels[mGame.mCurLevel][mRow][mCol] = '.';
    mGame.mCharacter.setKey(true);
    mActivated = true;
}

Game::Apple::Apple(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Apple::draw()
{
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    move();
}

void Game::Apple::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    mGame.mGameObjects[mRow + dr][mCol + dc].swap(mGame.mGameObjects[mRow][mCol]);
    swap(mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc], mGame.mLevels[mGame.mCurLevel][mRow][mCol]);

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
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    }
    return true;
}

Game::Ball::Ball(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c)
{
}

void Game::Ball::draw()
{
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    move();
}

void Game::Ball::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    mGame.mGameObjects[mRow + dr][mCol + dc].swap(mGame.mGameObjects[mRow][mCol]);
    swap(mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc], mGame.mLevels[mGame.mCurLevel][mRow][mCol]);

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
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    }
    return true;
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
    mGame.mLevels[mGame.mCurLevel][mRow][mCol] = '.';
    mGame.mGameObjects[mRow][mCol].release();
    mActivated = true;
    mGame.prepareNextLevel();
}

Game::Bomb::Bomb(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c), mActivated(false)

{
}

void Game::Bomb::draw()
{
    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f,
                                                      mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (curState == State::Moving || mActivated)
    {
        ++mCounter;
        if (--mCounterExp == 0)
        {
            mAnimationIndex = 1;
            mFrameIndex = 0;
        }
        cout << mCounterExp << endl;

        if (mCounter == MaxCount)
        {
            if (mFrameIndex == 1 && mCounterExp < 0)
            {
                mGame.mLevels[mGame.mCurLevel][mRow][mCol] = '.';
                if (mGame.mLevels[mGame.mCurLevel][mRow][mCol - 1] != '.' && mGame.mLevels[mGame.mCurLevel][mRow][mCol - 1] != 'W')
                {
                    mGame.mGameObjects[mRow][mCol - 1].release();
                }
                mGame.mGameObjects[mRow][mCol].release();
                return;
            }
            else
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
            }
        }
    }
    move();
}

void Game::Bomb::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    mGame.mGameObjects[mRow + dr][mCol + dc].swap(mGame.mGameObjects[mRow][mCol]);
    swap(mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc], mGame.mLevels[mGame.mCurLevel][mRow][mCol]);

    mDirection.x = distOfStep * dc;
    mDirection.y = distOfStep * dr;
    mRow += dr;
    mCol += dc;
    curState = State::Moving;
    mActivated = true;
    mCounterExp = 200;
}

bool Game::Bomb::move()
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
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    }
    return true;
}

Game::BadCat::BadCat(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c), mActivated(false)

{
}

void Game::BadCat::activate()
{
    if (curState == State::Standing)
    {
        mActivated = true;
        mCounterExp = 100;
    }
}

void Game::BadCat::draw()
{
    if (curState == State::Standing && !mActivated)
    {
        if (mGame.mLevels[mGame.mCurLevel][mRow - 1][mCol] == 'R' || mGame.mLevels[mGame.mCurLevel][mRow + 1][mCol] == 'R' ||
            mGame.mLevels[mGame.mCurLevel][mRow][mCol - 1] == 'R' || mGame.mLevels[mGame.mCurLevel][mRow][mCol + 1] == 'R')
        {
            activate();
            if (auto p = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow + 1][mCol].get()))
            {
                p->activate();
            }
            if (auto p1 = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow - 1][mCol].get()))
            {
                p1->activate();
            }
            if (auto p2 = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow][mCol - 1].get()))
            {
                p2->activate();
            }
            if (auto p3 = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow][mCol + 1].get()))
            {
                p3->activate();
            }
        }
    }

    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f,
                                                      mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (mActivated)
    {
        ++mCounter;
        if (--mCounterExp == 0)
        {
            mAnimationIndex = 1;
            mFrameIndex = 0;
        }

        if (mCounter == MaxCount)
        {
            if (mFrameIndex == 1 && mCounterExp < 0)
            {
                mGame.mLevels[mGame.mCurLevel][mRow][mCol] = '.';
                mGame.mGameObjects[mRow][mCol].release();
                return;
            }
            else
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1) % mSprites[mAnimationIndex].size();
            }
        }
    }
    move();
}

void Game::BadCat::startMove(int dr, int dc)
{
    mNumOfSteps = MaxCount * 4;
    float distOfStep = mGame.mCellSize / mNumOfSteps;

    dRow = dr;
    dCol = dc;

    mDirection.x = distOfStep * dc;
    mDirection.y = distOfStep * dr;

    curState = State::Moving;
}

bool Game::BadCat::move()
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

            mGame.mGameObjects[mRow + dRow][mCol + dCol].swap(mGame.mGameObjects[mRow][mCol]);
            swap(mGame.mLevels[mGame.mCurLevel][mRow + dRow][mCol + dCol], mGame.mLevels[mGame.mCurLevel][mRow][mCol]);

            mRow += dRow;
            mCol += dCol;
        }
        mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    }
    return true;
}

Game::Snake::Snake(Game &game, const string &path, int r, int c)
    : GameObject(game, path, r, c), mActivated(false)

{
    mSprites.resize(2);
    sf::Texture text;

    if (!text.loadFromFile("data/snake_left.png"))
    {
        cout << "catn load left" << endl;
    }
    mTextures.push_back(text);
    mSprites[1].push_back(make_unique<sf::Sprite>(mTextures.back()));

    if (!text.loadFromFile("data/snake_up.png"))
    {
        cout << "catn load up" << endl;
    }
    mTextures.push_back(text);
    mSprites[1].push_back(make_unique<sf::Sprite>(mTextures.back()));

    if (!text.loadFromFile("data/snake_right.png"))
    {
        cout << "catn load right" << endl;
    }
    mTextures.push_back(text);
    mSprites[1].push_back(make_unique<sf::Sprite>(mTextures.back()));

    if (!text.loadFromFile("data/snake_down.png"))
    {
        cout << "catn load down" << endl;
    }
    mTextures.push_back(text);
    mSprites[1].push_back(make_unique<sf::Sprite>(mTextures.back()));
}

void Game::Snake::draw()
{
    float originX;
    float originY;
    if (mAnimationIndex == 0)
    {
        originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f;
        originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f;
    }
    else
    {
        if (mFrameIndex == 0)
        {
            originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width - mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
        else if (mFrameIndex == 1)
        {
            originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height - mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
        else if (mFrameIndex == 2)
        {
            originX = mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
        else if (mFrameIndex == 3)
        {
            originX = mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f;
            originY = mSprites[mAnimationIndex - 1][mFrameIndex]->getLocalBounds().height / 2.0f;
        }
    }

    mSprites[mAnimationIndex][mFrameIndex]->setOrigin(originX, originY);
    mSprites[mAnimationIndex][mFrameIndex]->setScale(4, 4);
    mSprites[mAnimationIndex][mFrameIndex]->setPosition(mX, mY);
    mGame.mWindow.draw(*mSprites[mAnimationIndex][mFrameIndex]);
    if (mActivated)
    {
        ++mCounter;

        if (curState == State::Standing)
        {
            if (mCounter == MaxCount)
            {
                mCounter = 0;

                if ((mFrameIndex + 1) < mSprites[mAnimationIndex].size())
                {
                    mFrameIndex += 1;
                }
                else
                {
                    curState = State::Moving;
                    mActivated = false;
                }
            }
        }

        if (mCounter == MaxCount * 4 && curState == State::Moving)
        {
            mCounter = 0;
            mFrameIndex = mSprites[mAnimationIndex].size() - 1;
            mAnimationIndex = 0;
            mActivated = false;
        }
    }
    move();
}

bool Game::Snake::move()
{
    if (curState == State::Standing)
    {
        if (mGame.mCharacter.getRow() == mRow)
        {
            if (mGame.mCharacter.getCol() == mCol - 1 || mGame.mCharacter.getCol() == mCol + 1)
            {
                mActivated = true;
            }
        }
        else if (mGame.mCharacter.getCol() == mCol)
        {
            if (mGame.mCharacter.getRow() == mRow - 1 || mGame.mCharacter.getRow() == mRow + 1)
            {
                mActivated = true;
            }
        }
    }
    else
    {
        if (!mGame.mCharacter.isCaught())
        {
            if (mGame.mCharacter.getRow() == mRow)
            {
                if (mGame.mCharacter.getCol() == mCol - 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 0;
                    mActivated = true;
                    mGame.mCharacter.setCaught();
                }
                else if (mGame.mCharacter.getCol() == mCol + 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 2;
                    mActivated = true;
                    mGame.mCharacter.setCaught();
                }
            }
            else if (mGame.mCharacter.getCol() == mCol)
            {
                if (mGame.mCharacter.getRow() == mRow - 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 1;
                    mActivated = true;
                    mGame.mCharacter.setCaught();
                }
                else if (mGame.mCharacter.getRow() == mRow + 1)
                {
                    mAnimationIndex = 1;
                    mFrameIndex = 3;
                    mActivated = true;
                    mGame.mCharacter.setCaught();
                }
            }
        }
    }
    return true;
}

// MainCharacter
Game::MainCharacter::MainCharacter(Game &game)
    : mGame(game),
      mCounter(0), mAnimationIndex(0), mFrameIndex(0), curState(State::Standing), mDirection(sf::Vector2f(0.0f, 0.0f)),
      mNumOfSteps(MaxCount * 4), mDistOfSteps(32 * 4 / mNumOfSteps),
      mHasKey(false), mIsCaught(false)
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
    float x = (mGame.mWindow.getSize().x / 2.0f - mSprites[0][0]->getGlobalBounds().width * (mGame.mLevels[mGame.mCurLevel][0].size() / 2.0f)) + mSprites[0][0]->getGlobalBounds().width * col;
    float y = (mGame.mWindow.getSize().y / 2.0f - mSprites[0][0]->getGlobalBounds().width * (mGame.mLevels[mGame.mCurLevel].size() / 2.0f)) + mSprites[0][0]->getGlobalBounds().width * row;
    mCoords = sf::Vector2f(x, y);
}

void Game::MainCharacter::draw()
{
    if (!mIsCaught)
    {
        mSprites[mAnimationIndex][mFrameIndex]->setOrigin(mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f,
                                                          mSprites[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
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
}

bool Game::MainCharacter::canMove(int dr, int dc) const
{
    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == '.')
    {
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'A' &&
        mGame.mLevels[mGame.mCurLevel][mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Apple *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'B' &&
        mGame.mLevels[mGame.mCurLevel][mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Ball *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'E' &&
        mGame.mLevels[mGame.mCurLevel][mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<Bomb *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'R' &&
        mGame.mLevels[mGame.mCurLevel][mRow + dr + dr][mCol + dc + dc] == '.')
    {
        auto p = dynamic_cast<BadCat *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->startMove(dr, dc);
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'F')
    {
        auto p = dynamic_cast<Flower *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'M')
    {
        auto p = dynamic_cast<Mouse *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return true;
    }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'K')
    {
        auto p = dynamic_cast<Key *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return true;
    }

    // if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'S')
    // {
    //     auto p = dynamic_cast<Snake *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
    //     p->activate();
    //     return false;
    // }

    if (mGame.mLevels[mGame.mCurLevel][mRow + dr][mCol + dc] == 'D')
    {
        auto p = dynamic_cast<Door *>(mGame.mGameObjects[mRow + dr][mCol + dc].get());
        p->activate();
        return p->getActivStatus();
    }

    return false;
}

void Game::MainCharacter::setKey(bool b)
{
    mHasKey = b;
}

bool Game::MainCharacter::getKey()
{
    return mHasKey;
}

void Game::MainCharacter::setCaught()
{
    mIsCaught = true;
}

bool Game::MainCharacter::isCaught()
{
    return mIsCaught;
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