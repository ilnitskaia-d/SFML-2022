#include "Rect.hpp"

using namespace std;

Rect::~Rect()
{
    std::cout << "~Rect()" << std::endl;
}

void Rect::draw(Screen &scree)
{
    for(int i = 0; i < mH; i++)
    {
        for(int j = 0; j < mW; j++)
        {
            scree.put(mX + j, mY + i);
        }
    }
}
void Rect::save(ostream &file) const
{
    file << "Rect " << mX << " " << mY << "\n";
}