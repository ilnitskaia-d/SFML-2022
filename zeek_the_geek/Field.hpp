#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

using namespace std;

class Field
{
    sf::RenderWindow &mWindow;
    size_t curLevelIndex;
    sf::Texture mWallTexture;
    sf::Texture mFloorTexture;
    vector<vector<string>> mLevels;
    vector<unique_ptr<sf::Sprite>> mField;

public:
    Field(sf::RenderWindow &window);
    void draw();

private:
    bool loadLevels();
    void loadTiles(size_t level);
};