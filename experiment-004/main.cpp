#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    window.setVerticalSyncEnabled(true);

    // vector<vector<int>> puzzle = {{0, 2, 8, 16}, {32, 0, 64, 128}};

    sf::Texture texture2048;
    texture2048.loadFromFile("data/2048.png");
    sf::Sprite sprite;
    sprite.setTexture(texture2048);
    sprite.setPosition(sf::Vector2f(window.getSize().x / 2 - sprite.getLocalBounds().width / 2, window.getSize().y / 2 - sprite.getLocalBounds().height / 2));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
#ifdef AUCA_DEBUG
                // std::clog << sound.getVolume() << std::endl;
#endif
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

#ifdef AUCA_DEBUG
    std::clog << "ok" << std::endl;
#endif
}