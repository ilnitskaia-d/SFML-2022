#include <iostream>
#include <cstdint>

using namespace std;

string toBinary(int32_t u)
{
    uint32_t mask = 1;
    string res(32, '0');
    for (int i = 0; i < 32; i++, mask <<= 1)
    {
        if(u & mask)
        {
            res[i] = '1';
        }
    }
    return res;
}

int main()
{
    int32_t x;
    cin >> x;
    cout << toBinary(x) << endl;
}