#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    window.setVerticalSyncEnabled(true);

    vector<vector<int>> puzzle = {{0, 2, 8, 16}, {32, 4, 64, 128}, {256, 512, 1024, 0}, {2048, 2, 0, 128}};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Texture texture;
        texture.loadFromFile("data/2.png");
        sf::Sprite sprite;
        sprite.setTexture(texture);
        float x = window.getSize().x / 2 - sprite.getLocalBounds().width * 2;
        float y = window.getSize().y / 2 - sprite.getLocalBounds().height * 2;
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
                    window.draw(sprite);
                }
                x += sprite.getLocalBounds().width;
            }
            x = window.getSize().x / 2 - sprite.getLocalBounds().width * 2;
            y += sprite.getLocalBounds().height;
        }

        window.display();
    }

#ifdef AUCA_DEBUG
    std::clog << "ok" << std::endl;
#endif
}