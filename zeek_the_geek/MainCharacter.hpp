#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Field.hpp"

using namespace std;

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

    sf::RenderWindow &mWindow;
    Field &mField;
    sf::Vector2f mCoords;
    
    int mCounter;
    size_t mAnimationIndex;
    size_t mFrameIndex;
    
    State curState;
    sf::Vector2f mDirection;

public:
    MainCharacter(sf::RenderWindow &window, Field &field, float x, float y);

    void move();
    void draw();
};