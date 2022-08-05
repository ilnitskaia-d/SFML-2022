#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Button
{
    int mLeftUpperX;
    int mLeftUpperY;
    int mWidth;
    int mHeight;
    void (*ptrToFunc)();

public:
    Button(int leftUpperX, int leftUpperY, int width, int height, void ptr())
        : mLeftUpperX(leftUpperX), mLeftUpperY(leftUpperY), mWidth(width), mHeight(height), ptrToFunc(ptr)
    {
    }

    bool contains(int x, int y) const
    {
        return mLeftUpperX <= x && x <= mLeftUpperX + mWidth &&
               mLeftUpperY <= y && y <= mLeftUpperY + mHeight;
    }

    void run() const
    {
        ptrToFunc();
    }
};

void printSmt()
{
    cout << "Something" << endl;
}

void printTab()
{
    for(int i = 0; i < 10; i++)
    {
        cout << i << " ";
    }
    cout << endl;
}

void printHi()
{
    cout << "Hello, world" << endl;
}

int main()
{
    vector<Button> buttons = {
        Button(0, 0, 5, 5, printSmt),
        Button(5, 5, 5, 5, printTab),
        Button(10, 10, 5, 5, printHi)};

    for (int x, y; cin >> x >> y;)
    {
        for (Button &b : buttons)
        {
            if (b.contains(x, y))
            {
                b.run();
            }
        }
    }
}