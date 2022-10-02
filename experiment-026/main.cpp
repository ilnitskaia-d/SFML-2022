#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML app");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(100, 100));
    float shapeX = window.getSize().x / 2 - shape.getSize().x;
    float shapeY = window.getSize().y / 2 - shape.getSize().y;
    shape.setPosition(sf::Vector2f(shapeX, shapeY));
    shape.setFillColor(sf::Color::Red);

    sf::FloatRect rect(shape.getPosition(), shape.getSize());

    cout << "Rect shape : " << endl;
    cout << "x coord : " << shape.getPosition().x << endl;
    cout << "y coord : " << shape.getPosition().y << endl;
    cout << "width : " << shape.getSize().x << endl;
    cout << "height : " << shape.getSize().y << endl;

    cout << endl;

    cout << "Float rect : " << endl;
    cout << "left : " << rect.left << endl;
    cout << "top : " << rect.top << endl;
    cout << "height : " << rect.height << endl;
    cout << "width : " << rect.width << endl;
}