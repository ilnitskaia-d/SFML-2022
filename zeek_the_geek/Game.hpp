#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameObj.hpp"
#include "MainCharacter.hpp"

using namespace std;

class Game
{
    sf::RenderWindow mWindow;
    vector<unique_ptr<GameObj>> mField;
    MainCharacter mCharacter;

public:
    Game();
    void run();
};