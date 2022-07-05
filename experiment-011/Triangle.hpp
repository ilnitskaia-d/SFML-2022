#pragma once
#include "Shape.hpp"

class Triangle : public Shape
{
    int mH;

public:
    Triangle(int x, int y, int h)
        : Shape(x, y), mH(h)
    {
    }

    ~Triangle();

    void draw(Screen &scree) override;
    void save(std::ostream &file) const override;
};