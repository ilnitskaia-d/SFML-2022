#include "renderer.hpp"

Renderer::Renderer(Game2048 &game)
    : mGame(game)
{
    std::vector<int> nums = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

    sf::Texture numsText;
    numsText.loadFromFile("data/nums.png");
    int pos = 0;
    for (auto n : nums)
    {
        mTilesTextures.emplace(n, sf::Sprite(numsText, sf::IntRect(pos, 0, 100, 100)));
        pos += 100;
    }
}
void Renderer::render(sf::RenderWindow &window) const
{
    float x = window.getSize().x / 2 - 200;
    float y = window.getSize().y / 2 - 200;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mGame.getAt(i, j) != 0)
            {
                
            }
            x += 100;
        }
        x = window.getSize().x / 2 - 100;
        y += 100;
    }
}

void Renderer::renderConsole() const
{
    std::cout << "Score: " << mGame.getCurrScore() << std::endl;
    std::cout << "Best Score: " << mGame.getBestScore() << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << std::setw(5) << mGame.getAt(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void Renderer::renderFrames(sf::RenderWindow &window)
{
    while (!mGame.isFramesEmpty())
    {
        sf::Texture texture;
        // texture.loadFromFile("data/2.png");
        sf::Sprite sprite;
        // sprite.setTexture(texture);
        float x = window.getSize().x / 2 - 200;
        float y = window.getSize().y / 2 - 200;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (mGame.getAt(i, j) != 0)
                {
                    switch (mGame.getAt(i, j))
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
                    window.draw(sprite);
                }
                x += 100;
            }
            x = window.getSize().x / 2 - 100;
            y += sprite.getLocalBounds().height;
        }
    }
}
