#include <iostream>
#include <vector>

using namespace std;

class Puzzle
{
    vector<vector<int>> field;
    int size = 4;

public:
    Puzzle()
        : field(size, vector<int>(size))
    {
    }

    void readInput()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cin >> field[i][j];
            }
        }
    }

    bool canMove(int a, int b)
    {
        return (a == b && a != 0) || a == 0 || b == 0;
    }

    void moveLeft()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 1; j < size; j++)
            {
                int b = j;

                while (field[i][b] == 0)
                {
                    b++;
                    if (b == size)
                    {
                        b--;
                        break;
                    }
                }

                if ((field[i][j - 1] == field[i][b]) || (field[i][j - 1] == 0))
                {
                    field[i][j - 1] += field[i][b];
                    field[i][b] = 0;
                }
            }
        }
    }

    void moveRight()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = size - 1; j > 0; j--)
            {
                int b = j - 1;

                while (field[i][b] == 0)
                {
                    b--;
                    if (b < 0)
                    {
                        b++;
                        break;
                    }
                }

                if ((field[i][j + 1] == field[i][b]) || (field[i][j + 1] == 0))
                {
                    field[i][j + 1] += field[i][b];
                    field[i][b] = 0;
                }
            }
        }
    }

    void solve(int step)
    {
        if (step == 0)
        {
            moveLeft();
        }
        else if (step == 1)
        {
            // moveUp();
        }
        else if (step == 2)
        {
            moveRight();
        }
        else
        {
            // moveDown();
        }

        print();
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << field[i][j] << (j == size - 1 ? "\n" : " ");
            }
        }
    }
};

int main()
{
    Puzzle puzzle;

    puzzle.readInput();
    int step;
    cin >> step;
    puzzle.solve(step);
}