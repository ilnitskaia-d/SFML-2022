#pragma once
#include "GameObj.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class MainCharacter : public GameObj
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

    vector<vector<unique_ptr<sf::Sprite>>> mSprites;
    int mCounter;
    size_t mAnimationIndex;
    size_t mFrameIndex;
    State curState;

public:
    MainCharacter(sf::RenderWindow &window, float x, float y);

    void move();

    void draw() override;
};