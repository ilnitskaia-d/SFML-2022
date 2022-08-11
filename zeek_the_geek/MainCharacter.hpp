#pragma once
#include "GameObj.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class MainCharacter : public GameObj
{
    vector<vector<unique_ptr<sf::Sprite>>> mSprites;
    int mCounter;
    size_t mAnimationIndex;
    size_t mFrameIndex;

public:
    MainCharacter(sf::RenderWindow &window, float x, float y);

    void move(sf::Event event);

    void draw() override;
};