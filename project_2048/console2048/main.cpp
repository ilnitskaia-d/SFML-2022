#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    int goal = 0;

    if (argc == 1)
    {
        goal = 16;
    }
    else if (argc == 2)
    {
        int inp;
        char ch;
        istringstream sinp(argv[1]);
        if (sinp >> inp && !(sinp >> ch))
        {
            if (binary_search(v.begin(), v.end(), inp))
            {
                goal = inp;
            }
            else
            {
                cout << "Can't use goal of : " << inp << endl;
                exit(1);
            }
        }

        if(goal == 0)
        {
            goal = 16;
        }
    }
    else
    {
        cout << "Wrong input\n";
        exit(1);
    }

    cout << goal << endl;
    // for (int i = 0; i < argc; ++i)
    // {
    //     cout << argv[i] << endl;
    // }
}