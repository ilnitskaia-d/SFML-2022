#pragma once
#include "Screen.hpp"
#include <iostream>

class Shape // abstract
{
protected:
    int mX;
    int mY;

public:
    Shape(int x, int y)
        : mX(x), mY(y)
    {
    }

    virtual ~Shape() { std::cout << "~Shape()" << std::endl; }
    virtual void draw(Screen &screen) = 0;
    virtual void save(std::ostream &file) const = 0;
};