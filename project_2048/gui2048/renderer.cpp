#include "renderer.hpp"

using namespace std;

Renderer::Renderer(Game2048 &game, sf::RenderWindow &window, sf::Font &font)
    : mGame(game), mWindow(window), mFont(font)
{
    mBlockSize = min(mWindow.getSize().x, mWindow.getSize().y) / 8;

    nameText.setFont(mFont);
    nameText.setString("Game 2048");
    nameText.setCharacterSize(50);
    nameText.setFillColor(sf::Color::Magenta);
    float x = mWindow.getSize().x / 2 - nameText.getLocalBounds().width / 2;
    float y = 0 + nameText.getLocalBounds().height / 2;
    nameText.setPosition(sf::Vector2f(x, y));

    goalText.setFont(mFont);
    goalText.setCharacterSize(40);
    goalText.setFillColor(sf::Color::Magenta);

    bestScoreText.setFont(mFont);
    bestScoreText.setCharacterSize(40);
    bestScoreText.setFillColor(sf::Color::Magenta);

    currScoreText.setFont(mFont);
    currScoreText.setCharacterSize(40);
    currScoreText.setFillColor(sf::Color::Magenta);
}

void Renderer::render()
{
    vector<vector<int>> puzzle = mGame.getNextFrame();

    float x = mWindow.getSize().x / 2 - mBlockSize * 2;
    float y = mWindow.getSize().y / 2 - mBlockSize * 2;

    mWindow.draw(nameText);

    goalText.setString("Goal: \n" + to_string(mGame.getGoal()));
    goalText.setPosition(sf::Vector2f(x - goalText.getLocalBounds().width, mWindow.getSize().y / 4 + goalText.getLocalBounds().height));
    mWindow.draw(goalText);

    currScoreText.setString("Score: \n" + to_string(mGame.getCurrScore()));
    currScoreText.setPosition(sf::Vector2f(mWindow.getSize().x / 2 + mBlockSize * 2 + currScoreText.getLocalBounds().width / 4, mWindow.getSize().y / 4 + currScoreText.getLocalBounds().height));
    mWindow.draw(currScoreText);
    bestScoreText.setString("Best: \n" + to_string(mGame.getBestScore()));
    bestScoreText.setPosition(sf::Vector2f(currScoreText.getPosition().x, currScoreText.getPosition().y + currScoreText.getLocalBounds().height * 2));
    mWindow.draw(bestScoreText);

    sf::RectangleShape field;
    field.setSize(sf::Vector2f(mBlockSize * 4, mBlockSize * 4));
    field.setPosition(sf::Vector2f(x, y));
    sf::Color color(170, 170, 170);
    field.setFillColor(color);
    field.setOutlineColor(color);
    field.setOutlineThickness(10);
    mWindow.draw(field);

    sf::Texture texture;
    sf::Sprite sprite;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (puzzle[i][j] != 0)
            {
                switch (puzzle[i][j])
                {
                case 2:
                    texture.loadFromFile("data/2.png");
                    break;
                case 4:
                    texture.loadFromFile("data/4.png");
                    break;
                case 8:
                    texture.loadFromFile("data/8.png");
                    break;
                case 16:
                    texture.loadFromFile("data/16.png");
                    break;
                case 32:
                    texture.loadFromFile("data/32.png");
                    break;
                case 64:
                    texture.loadFromFile("data/64.png");
                    break;
                case 128:
                    texture.loadFromFile("data/128.png");
                    break;
                case 256:
                    texture.loadFromFile("data/256.png");
                    break;
                case 512:
                    texture.loadFromFile("data/512.png");
                    break;
                case 1024:
                    texture.loadFromFile("data/1024.png");
                    break;
                case 2048:
                    texture.loadFromFile("data/2048.png");
                    break;
                }
                sprite.setTexture(texture);
                sprite.setScale(sf::Vector2f(mBlockSize / texture.getSize().x, mBlockSize / texture.getSize().y));
                sprite.setPosition(sf::Vector2f(x, y));
                mWindow.draw(sprite);
            }
            x += mBlockSize;
        }
        x = mWindow.getSize().x / 2 - mBlockSize * 2;
        y += mBlockSize;
    }
}
