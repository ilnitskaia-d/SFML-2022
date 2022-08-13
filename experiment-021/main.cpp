#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct B
{
    virtual void commonMethod() const = 0;
};

struct D1 : B
{
    void commonMethod() const override
    {
        cout << "D1::commonMethod" << endl;
    }

    void d1Method() const
    {
        cout << "D1::d1Method" << endl;
    }
};

struct D2 : B
{
    void commonMethod() const override
    {
        cout << "D2::commonMethod" << endl;
    }

    void d2Method() const
    {
        cout << "D2::d2Method" << endl;
    }
};

int main()
{
    vector<unique_ptr<B>> items;

    items.push_back(make_unique<D1>());
    items.push_back(make_unique<D2>());

    for(const auto &p : items)
    {
        p->commonMethod();
        if(auto p1 = dynamic_cast<D1*>(p.get()))
        {
            p1->d1Method();
        }
        else if(auto p2 = dynamic_cast<D2*>(p.get()))
        {
            p2->d2Method();
        }
    }
}