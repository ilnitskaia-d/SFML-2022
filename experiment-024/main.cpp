#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;

bool loadLevels(vector<vector<string>> &levels)
{
    std::fstream level("data/levels.data");
    if (!level)
    {
        std::cout << "file not found" << std::endl;
        return false;
    }
    for (;;)
    {
        std::string line;
        if (!std::getline(level, line))
        {
            break;
        }

        if (!std::getline(level, line))
        {
            return false;
        }

        int h;
        std::istringstream sinp(line);
        if (!(sinp >> h))
        {
            return false;
        }

        std::vector<std::string> curLevel;
        for (int i = 0; i < int(h); i++)
        {
            if (!std::getline(level, line))
            {
                return false;
            }
            curLevel.push_back(line);
        }

        levels.push_back(curLevel);
    }

    return true;
}

sf::Vector2f loadTiles(vector<string> &curMap, vector<unique_ptr<sf::RectangleShape>> &walls, vector<unique_ptr<sf::FloatRect>> &field, float cX, float cY)
{
    float chX;
    float chY;

    field.resize(curMap.size() * curMap[0].size());
    walls.resize(curMap.size() * curMap[0].size());
    for (size_t r = 0; r < curMap.size(); r++)
    {
        for (size_t c = 0; c < curMap[r].size(); c++)
        {
            if (curMap[r][c] == 'W')
            {
                float x = cX + 100 * c;
                float y = cY + 100 * r;
                field.push_back(make_unique<sf::FloatRect>(x, y, 100, 100));
                walls.push_back(make_unique<sf::RectangleShape>());
                walls.back()->setSize(sf::Vector2f(100, 100));
                walls.back()->setPosition(x, y);
                // walls.back()->setOutlineThickness(3);
                // walls.back()->setOutlineColor(sf::Color::Magenta);
            }
            else if (curMap[r][c] == 'C')
            {
                chX = cX + 100 * c;
                chY = cY + 100 * r;
            }
        }
    }
    return sf::Vector2f(chX, chY);
}

bool checkWall(const sf::FloatRect &rect, const vector<unique_ptr<sf::FloatRect>> &field)
{
    for (auto &r : field)
    {
        if (r)
        {
            if (r->intersects(rect))
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML app");
    window.setVerticalSyncEnabled(true);

    vector<vector<string>> levels;
    loadLevels(levels);

    float cX = window.getSize().x / 2.0f - 100 * (levels[0][0].size() / 2.0f);
    float cY = window.getSize().y / 2.0f - 100 * (levels[0].size() / 2.0f);

    vector<unique_ptr<sf::RectangleShape>> walls;
    vector<unique_ptr<sf::FloatRect>> field;
    sf::Vector2f pos = loadTiles(levels[0], walls, field, cX, cY);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(100, 100));
    float shapeX = pos.x;
    float shapeY = pos.y;
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Red);

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
                int step = shape.getSize().x / 10;

                if (event.key.code == sf::Keyboard::Left)
                {
                    sf::FloatRect rect(sf::Vector2f(shapeX - step, shapeY), shape.getSize());
                    if (shapeX - step > shape.getSize().x && shapeX - step < window.getSize().x - shape.getSize().x && checkWall(rect, field))
                    {
                        shapeX -= step;
                    }
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    sf::FloatRect rect(sf::Vector2f(shapeX + step, shapeY), shape.getSize());
                    if (shapeX + step > shape.getSize().x && shapeX + step < window.getSize().x - shape.getSize().x && checkWall(rect, field))
                    {
                        shapeX += step;
                    }
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    sf::FloatRect rect(sf::Vector2f(shapeX, shapeY - step), shape.getSize());
                    if (shapeY - step > 0 && shapeY - step < window.getSize().x - shape.getSize().y && checkWall(rect, field))
                    {
                        shapeY -= step;
                    }
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    sf::FloatRect rect(sf::Vector2f(shapeX, shapeY + step), shape.getSize());
                    if (shapeY + step > 0 && shapeY + step < window.getSize().y - shape.getSize().y && checkWall(rect, field))
                    {
                        shapeY += step;
                    }
                }
                shape.setPosition(sf::Vector2f(shapeX, shapeY));
            }
        }

        window.clear();
        window.draw(shape);
        for (const auto &w : walls)
        {
            if (w)
            {
                window.draw(*w);
            }
        }
        window.display();
    }
}