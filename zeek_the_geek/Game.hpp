#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

// #include "MainCharacter.hpp"

using namespace std;

class Game
{
    class GameObject
    {
    protected:
        Game &mGame;
        sf::Texture mTexture;
        sf::Sprite mSprite;
        int mRow;
        int mCol;
        float mX;
        float mY;

    public:
        GameObject(Game &game, const string &path, int r, int c);

        virtual void draw() = 0;
        virtual float getX()
        {
            return mX;
        }

        virtual float getY()
        {
            return mY;
        }

        virtual float getSize()
        {
            return mSprite.getGlobalBounds().width;
        }

        virtual bool cantMove(float x, float y, float size)
        {
            return (mX - mSprite.getGlobalBounds().width / 2.0f < size + x && x - size < mX + mSprite.getGlobalBounds().width / 2.0f &&
                    mY - mSprite.getGlobalBounds().height / 2.0f < y + size && y - size < mY + mSprite.getGlobalBounds().height / 2.0f);
        };
    };

    struct IMovable
    {
        virtual bool move(int dx, int dy) = 0;
    };

    class Wall : public GameObject
    {
    public:
        Wall(Game &game, const string &path, int r, int c);
        void draw() override;
    };

    class Flower : public GameObject
    {
    public:
        Flower(Game &game, const string &path, int r, int c);
        void draw() override;
    };

    class Apple : public GameObject, IMovable
    {
    public:
        Apple(Game &game, const string &path, int r, int c);
        void draw() override;
        bool move(int dx, int dy) override;
    };

    class Ball : public GameObject, IMovable
    {
    public:
        Ball(Game &game, const string &path, int r, int c);
        void draw() override;
        bool move(int dx, int dy) override;
    };

    class MainCharacter
    {
        enum State
        {
            goLeft,
            goRight,
            goUp,
            goDown,
            standLeft,
            standRight,
            standUp,
            standDown,
        };

        sf::Texture mTexture;
        vector<vector<unique_ptr<sf::Sprite>>> mSprites;

        Game &mGame;
        sf::Vector2f mCoords;

        int mCounter;
        size_t mAnimationIndex;
        size_t mFrameIndex;

        State curState;
        sf::Vector2f mDirection;

    public:
        MainCharacter(Game &game);

        void move();
        void draw();
        void setCoords(int row, int col);
    };

private:
    sf::RenderWindow mWindow;
    MainCharacter mCharacter;
    vector<vector<string>> mLevels;
    vector<vector<unique_ptr<GameObject>>> mGameObjects;

    bool loadLevels();
    void loadTiles(size_t level);

public:
    Game();
    void run();
};