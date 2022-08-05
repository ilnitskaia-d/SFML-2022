#include <iostream>
#include <cmath>

using namespace std;

void printFunc(double beg, double end, double step, double ptrToFunc(double x))
{
    double x = beg;
    while (x <= end)
    {
        cout << x << " " << ptrToFunc(x) << endl;
        x += step;
    }
}

int main()
{
    printFunc(-5, 5, 1, abs);
    printFunc(0, 3.1415926, 0.2, sin);
}