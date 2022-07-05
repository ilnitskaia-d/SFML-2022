#include "Screen.hpp"
#include <iostream>

using namespace std;

Screen::Screen(int w, int h)
    : mCanvas(w, string(h, '.'))
{
}

void Screen::put(int x, int y)
{
    if (x >= 0 && x < (int)(mCanvas.size()) && y >= 0 && y < (int)(mCanvas.size()))
    {
        mCanvas[y][x] = '*';
    }
}

void Screen::print() const
{
    for(string s : mCanvas)
    {
        cout << s << endl;
    }
}

