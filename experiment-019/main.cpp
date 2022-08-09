#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Animation
{
    int mCounter;
    size_t mAnimationIndex;
    size_t mFrameIndex;
    sf::Texture mTexture;
    vector<vector<unique_ptr<sf::Sprite>>> mFrames;

public:
    Animation() : mCounter(0), mAnimationIndex(0), mFrameIndex(0)
    {

        if (!mTexture.loadFromFile("data/Wolfpack.png"))
        {
            cout << "failed to load from file" << endl;
            exit(1);
        }

        int frameW = mTexture.getSize().x / 3;
        int frameH = mTexture.getSize().y / 4;

        mFrames.resize(4);
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                mFrames[i].push_back(make_unique<sf::Sprite>(mTexture, sf::IntRect(j * frameW, i * frameH, frameW, frameH)));
                mFrames[i].back()->setScale(4, 4);
            }
        }
    }

    void setDirection(size_t index)
    {
        mFrameIndex = 0;
        mAnimationIndex = index;
    }

    void draw(sf::RenderWindow &window, sf::Vector2f coords)
    {
        mFrames[mAnimationIndex][mFrameIndex]->setPosition(coords);
        mFrames[mAnimationIndex][mFrameIndex]->setOrigin(mFrames[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f, mFrames[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
        window.draw(*mFrames[mAnimationIndex][mFrameIndex]);
        ++mCounter;
        if (mCounter == 5)
        {
            mCounter = 0;
            mFrameIndex = (mFrameIndex + 1) % mFrames[mAnimationIndex].size();
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
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                animation.setDirection(0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                animation.setDirection(1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                animation.setDirection(3);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                animation.setDirection(2);
            }
        }
        window.clear();
        animation.draw(window, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
        window.display();
    }
}