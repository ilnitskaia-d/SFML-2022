#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace std;

class Game
{
    class GameObject
    {
    protected:
        enum State
        {
            Moving,
            Standing,
            Sleeping
        };

        Game &mGame;
        sf::Texture mTexture;
        vector<vector<unique_ptr<sf::Sprite>>> mSprites;

        int mRow;
        int mCol;
        int dRow;
        int dCol;
        float mX;
        float mY;

        State curState;
        sf::Vector2f mDirection;
        const int MaxCount = 15;
        int mNumOfSteps;

        int mCounter;
        int mCounterExp;
        size_t mAnimationIndex;
        size_t mFrameIndex;

    public:
        GameObject(Game &game, const string &path, int r, int c);

        virtual void draw() = 0;

        virtual float getRow()
        {
            return mRow;
        }

        virtual float getCol()
        {
            return mCol;
        }

        virtual float getSize()
        {
            return mSprites[0][0]->getGlobalBounds().width;
        }
    };

    class Wall : public GameObject
    {
    public:
        Wall(Game &game, const string &path, int r, int c);
        void draw() override;
    };

    class Flower : public GameObject
    {
        bool mActivated = false;

    public:
        Flower(Game &game, const string &path, int r, int c);
        void draw() override;
        void activate();
    };

    class Door : public GameObject
    {
        bool mActivated = false;

    public:
        Door(Game &game, const string &path, int r, int c);
        void draw() override;
        void activate();
        bool getActivStatus()
        {
            return mActivated;
        }
    };

    class Key : public GameObject
    {
        bool mActivated = false;

    public:
        Key(Game &game, const string &path, int r, int c);
        void draw() override;
        void activate();
    };

    class Apple : public GameObject
    {
    public:
        Apple(Game &game, const string &path, int r, int c);
        void draw() override;
        void startMove(int dr, int dc);
        bool move();
    };

    class Ball : public GameObject
    {
    public:
        Ball(Game &game, const string &path, int r, int c);
        void draw() override;
        void startMove(int dr, int dc);
        bool move();
    };

    class Mouse : public GameObject
    {
        bool mActivated = false;

    public:
        Mouse(Game &game, const string &path, int r, int c);
        void draw() override;
        void activate();
    };

    class Bomb : public GameObject
    {
        bool mActivated;

    public:
        Bomb(Game &game, const string &path, int r, int c);
        void draw() override;
        void startMove(int dr, int dc);
        bool move();
    };

    class BadCat : public GameObject
    {
        bool mActivated;

        int dRow;
        int dCol;

    public:
        BadCat(Game &game, const string &path, int r, int c);
        void activate();
        void draw() override;
        void startMove(int dr, int dc);
        bool move();
    };

    class Snake : public GameObject
    {
        bool mActivated;
        vector<unique_ptr<sf::Texture>> mTextures;

    public:
        Snake(Game &game, const string &path, int r, int c);
        void draw() override;
        bool move();
        void attack(int dr, int dc);
    };

    class MainCharacter
    {
        enum State
        {
            Moving,
            Standing
        };

        sf::Texture mTexture;
        vector<vector<unique_ptr<sf::Sprite>>> mSprites;

        Game &mGame;
        sf::Vector2f mCoords;
        int mRow;
        int mCol;

        int mCounter;
        size_t mAnimationIndex;
        size_t mFrameIndex;

        State curState;
        sf::Vector2f mDirection;
        const int MaxCount = 15;
        int mNumOfSteps;
        int mDistOfSteps;

        bool mHasKey;
        bool mIsCaught;

    public:
        MainCharacter(Game &game);
        void reset();
        bool canMove(int dr, int dc) const;
        void move();
        void draw();
        void setCoords(int row, int col);
        void setKey(bool b);
        bool getKey();

        int getRow()
        {
            return mRow;
        }

        int getCol()
        {
            return mCol;
        }

        void setCaught(bool b);
        bool isCaught();
    };

private:
    sf::RenderWindow mWindow;
    MainCharacter mCharacter;
    vector<vector<string>> mLevels;
    vector<string> mCurMap;
    vector<vector<unique_ptr<GameObject>>> mGameObjects;
    float mCellSize;
    float mCenterX;
    float mCenterY;

    sf::Font mFont;
    sf::Text mScoreBar;
    int mScore;
    size_t mCurLevel;

    sf::Texture mFloorText;
    sf::Sprite mFloorSprite;

    bool loadLevels();
    void prepareNextLevel();
    void loadTiles(size_t level);

    void drawField();
    void restart();

public:
    Game();
    void run();
};