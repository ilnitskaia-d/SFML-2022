#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "MainCharacter.hpp"
#include "Field.hpp"

using namespace std;

class Game
{
    sf::RenderWindow mWindow;
    Field mField;
    MainCharacter mCharacter;

public:
    Game();
    void run();
};