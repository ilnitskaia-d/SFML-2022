#pragma once
#include "Shape.hpp"

class Rect : public Shape
{
    int mW;
    int mH;

public:
    Rect(int x, int y, int w, int h)
        : Shape(x, y), mW(w), mH(h)
    {
    }

    ~Rect();

    void draw(Screen &scree) override;
    void save(std::ostream &file) const override;
};