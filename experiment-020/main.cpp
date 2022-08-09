#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Animation
{
public:
    enum State
    {
        goLeft,
        goRight,
        goUp,
        goDown,
        standLeft,
        standRight,
        standUp,
        standDown,
    };

private:
    int mCounter;
    size_t mAnimationIndex;
    size_t mFrameIndex;
    State curState;
    sf::Texture mTexture;
    vector<vector<unique_ptr<sf::Sprite>>> mFrames;

public:
    Animation() : mCounter(0), mAnimationIndex(0), mFrameIndex(0), curState(State::standDown)
    {

        if (!mTexture.loadFromFile("data/texture.png"))
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
                mFrames[i].back()->setScale(6, 6);
            }
        }
    }

    void setState(State state)
    {
        mCounter = 0;
        mFrameIndex = 0;
        curState = state;
        switch (state)
        {
        case goLeft:
            mAnimationIndex = 2;
            break;
        case goRight:
            mAnimationIndex = 3;
            break;
        case goUp:
            mAnimationIndex = 1;
            break;
        case goDown:
            mAnimationIndex = 0;
            break;

        default:
            break;
        }
    }

    State getState()
    {
        return curState;
    }

    void draw(sf::RenderWindow &window, sf::Vector2f coords)
    {
        mFrames[mAnimationIndex][mFrameIndex]->setPosition(coords);
        mFrames[mAnimationIndex][mFrameIndex]->setOrigin(mFrames[mAnimationIndex][mFrameIndex]->getLocalBounds().width / 2.0f, mFrames[mAnimationIndex][mFrameIndex]->getLocalBounds().height / 2.0f);
        window.draw(*mFrames[mAnimationIndex][mFrameIndex]);
        if (curState == State::goLeft || curState == State::goRight || curState == State::goUp || curState == State::goDown)
        {
            ++mCounter;
            if (mCounter == 10)
            {
                mCounter = 0;
                mFrameIndex = (mFrameIndex + 1) % mFrames[mAnimationIndex].size();
            }
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
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && animation.getState() != Animation::State::goLeft)
            {
                cout << "left" << endl;
                animation.setState(Animation::State::goLeft);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && animation.getState() != Animation::State::goRight)
            {
                cout << "Right" << endl;
                animation.setState(Animation::State::goRight);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && animation.getState() != Animation::State::goUp)
            {
                animation.setState(Animation::State::goUp);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && animation.getState() != Animation::State::goDown)
            {
                animation.setState(Animation::State::goDown);
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
                     !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                if (animation.getState() == Animation::State::goLeft)
                {
                    animation.setState(Animation::State::standLeft);
                }
                else if (animation.getState() == Animation::State::goRight)
                {
                    animation.setState(Animation::State::standRight);
                }
                else if (animation.getState() == Animation::State::goUp)
                {
                    animation.setState(Animation::State::standUp);
                }
                else if (animation.getState() == Animation::State::goDown)
                {
                    animation.setState(Animation::State::standDown);
                }
            }
        }

        window.clear();
        animation.draw(window, sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
        window.display();
    }
}