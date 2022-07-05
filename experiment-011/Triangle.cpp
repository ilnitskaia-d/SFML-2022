#include "Triangle.hpp"

using namespace std;

Triangle::~Triangle()
{
    cout << "~Triangle()" << endl;
}

void Triangle::draw(Screen &screen)
{
    int curLen = 1;
    for (int row = 0; row < mH; row++)
    {
        for (int col = 0; col < curLen; col++)
        {
            screen.put(mX + col - curLen / 2, mY + row);
        }
        curLen += 2;
    }
}

void Triangle::save(ostream &file) const
{
    file << "Triangle " << mX << " " << mY << "\n";
}