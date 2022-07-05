#include <iostream>
#include "Screen.hpp"
#include "Shape.hpp"
#include "Rect.hpp"
#include "Triangle.hpp"
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

int main()
{
    Screen screen(20, 20);

    // Rect rect(3, 4, 4, 4);
    // rect.draw(screen);

    // Triangle triangle(12, 3, 3);
    // triangle.draw(screen);

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Triangle>(7, 12, 3));
    shapes.push_back(make_unique<Rect>(2, 5, 6, 4));

    ofstream fout("save.txt");

    for (const auto &p : shapes)
    {
        p->draw(screen);
        p->save(fout);
    }

    screen.print();
}