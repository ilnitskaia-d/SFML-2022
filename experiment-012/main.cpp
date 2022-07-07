// #include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ScreenSavers.hpp"
#include "SnowflakesFall.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    window.setVerticalSyncEnabled(true);
    
    SnowflakesFall bg(window);
    int dir = 0;
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

        window.clear();
        bg.draw(dir);
        window.display();
        dir++;
    }
}