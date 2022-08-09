#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <memory>

class Animation
{
    int counter;
    size_t index;
    std::vector<std::unique_ptr<sf::Texture>> textures;
    std::vector<std::unique_ptr<sf::Sprite>> frames;

public:
    Animation() : counter(0), index(0)
    {
        textures.reserve(6);
        frames.reserve(6);
        for (int i = 1; i <= 6; ++i)
        {
            std::string name = "data/star coin rotate/star coin rotate " + std::to_string(i) + ".png";
            textures.push_back(std::make_unique<sf::Texture>());
                if(textures.back()->loadFromFile(name))
                {
                    std::cout << "works" << std::endl;
                }

            frames.push_back(std::make_unique<sf::Sprite>());
            frames.back()->setTexture(*textures.back());
        }
    }

    void draw(sf::RenderWindow &window, sf::Vector2f coords)
    {
        frames[index]->setScale(sf::Vector2f(0.2f, 0.2f));
        frames[index]->setPosition(coords);
        frames[index]->setOrigin(frames[index]->getLocalBounds().width / 2.0f, frames[index]->getLocalBounds().height / 2.0f);
        window.draw(*frames[index]);
        ++counter;
        if (counter == 5)
        {
            counter = 0;
            index = (index + 1) % frames.size();
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML app", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    Animation animation;

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
        animation.draw(window, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
        window.display();
    }
}