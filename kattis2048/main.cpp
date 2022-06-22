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

                if (field[i][b] != 0)
                {
                    if ((field[i][j - 1] == field[i][b]) || (field[i][j - 1] == 0))
                    {
                        field[i][j - 1] += field[i][b];
                        field[i][b] = 0;
                    }
                }
            }
        }
    }

    void moveRight()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = size - 2; j > 0; j--)
            {
                int b = j;

                while (field[i][b] == 0)
                {
                    b--;
                    if (b < 0)
                    {
                        b++;
                        break;
                    }
                }

                if (field[i][b] != 0)
                {
                    if ((field[i][j + 1] == field[i][b]) || (field[i][j + 1] == 0))
                    {
                        field[i][j + 1] += field[i][b];
                        field[i][b] = 0;
                    }
                }
            }
        }
    }

    void moveUp()
    {
        for (int c = 0; c < size; c++)
        {
            for (int i = 1; i < size; i++)
            {
                int b = i;

                while (field[b][c] == 0)
                {
                    b++;
                    if (b == size)
                    {
                        b--;
                        break;
                    }
                }

                if (field[b][c] != 0)
                {
                    if ((field[i - 1][c] == field[b][c]) || (field[i - 1][c] == 0))
                    {
                        field[i - 1][c] += field[b][c];
                        field[b][c] = 0;
                    }
                }
            }
        }
    }

    void moveDown()
    {
        for (int c = 0; c < size; c++)
        {
            for (int i = size - 2; i > 0; i--)
            {
                int b = i;

                while (field[b][c] == 0)
                {
                    b--;
                    if (b < 0)
                    {
                        b++;
                        break;
                    }
                }

                if (field[b][c] != 0)
                {
                    if ((field[i + 1][c] == field[b][c]) || (field[i + 1][c] == 0))
                    {
                        field[i + 1][c] += field[b][c];
                        field[b][c] = 0;
                    }
                }
            }
        }
    }

    void solve(int step)
    {
        if (step == 0)
        {
            moveLeft();
            moveLeft();
        }
        else if (step == 1)
        {
            moveUp();
            moveUp();
        }
        else if (step == 2)
        {
            moveRight();
            moveRight();
        }
        else
        {
            moveDown();
            moveDown();
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