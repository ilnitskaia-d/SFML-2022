#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "MainCharacter.hpp"
#include "Field.hpp"

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
        void info() const
        {
            cout << "(" << mRow << " " << mCol << ") (" << mX << " " << mY << ")" << endl;
        }
    };

    struct IMovable
    {
        virtual bool move(int dx, int dy) = 0;
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

    sf::RenderWindow mWindow;
    Field mField;
    MainCharacter mCharacter;
    vector<vector<string>> mLevels;
    vector<vector<unique_ptr<GameObject>>> mGameObjects;

    bool loadLevels();
    void loadTiles(size_t level);
public:
    Game();
    void run();
};