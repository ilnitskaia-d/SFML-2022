#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    window.setVerticalSyncEnabled(true);

    sf::Music sound;
    if (!sound.openFromFile("data/music.wav"))
    {
        return 1;
    }
    sound.setVolume(100);
    sound.setLoop(true);
    sound.play();

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

        window.display();
    }

#ifdef AUCA_DEBUG
    std::clog << "ok" << std::endl;
#endif
}