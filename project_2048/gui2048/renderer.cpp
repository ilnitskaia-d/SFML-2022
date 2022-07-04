#include "renderer.hpp"

using namespace std;

Renderer::Renderer(Game2048 &game, sf::RenderWindow &window, sf::Font &font)
    : mGame(game), mWindow(window), mBlockSize(100), mFont(font)
{
    nameText.setFont(mFont);
    nameText.setString("Game 2048");
    nameText.setCharacterSize(50);
    nameText.setFillColor(sf::Color::Magenta);
    float x = mWindow.getSize().x / 2 - nameText.getLocalBounds().width / 2;
    float y = 0 + nameText.getLocalBounds().height;
    nameText.setPosition(sf::Vector2f(x, y));
    
}

void Renderer::renderText()
{
    // sf::Text winningText("Congrats!!!", font);
    // winningText.setCharacterSize(80);
    // winningText.setFillColor(sf::Color::Magenta);

    // sf::Text losingText("You lost", font);
    // losingText.setCharacterSize(80);
    // losingText.setFillColor(sf::Color::Red);
}

void Renderer::render()
{
    vector<vector<int>> puzzle = mGame.getNextFrame();

    float x = mWindow.getSize().x / 2 - mBlockSize * 2;
    float y = mWindow.getSize().y / 2 - mBlockSize * 2;

    sf::RectangleShape field;
    field.setSize(sf::Vector2f(mBlockSize * 4, mBlockSize * 4));
    field.setPosition(sf::Vector2f(x, y));
    sf::Color color(100, 100, 100);
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
                sprite.setPosition(sf::Vector2f(x, y));
                mWindow.draw(sprite);
            }
            x += 100;
        }
        x = mWindow.getSize().x / 2 - mBlockSize * 2;
        y += 100;
    }
    
    mWindow.draw(nameText);
}
