#include <iostream>
#include "..\libs\random.hpp"

using namespace std;
using Random = effolkronium::random_static;

int main()
{
    for(int i = 0; i < 10; i++)
    {
        int val = Random::get(1, 15);
        cout << val << endl;
    }
}