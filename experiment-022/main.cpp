#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main()
{
    vector<unique_ptr<string>> v;
    v.push_back(make_unique<string>("Hello"));
    v.push_back(nullptr);
    v.push_back(make_unique<string>("World"));

    for (auto &p : v)
    {
        if (p)
        {
            cout << *p << endl;
        }
        else
        {
            cout << "---" << endl;
        }
    }

    v[1].swap(v[2]);
    
    for (auto &p : v)
    {
        if (p)
        {
            cout << *p << endl;
        }
        else
        {
            cout << "---" << endl;
        }
    }
}