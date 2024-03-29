#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 4;

void readInput(vector<vector<int>> &field)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cin >> field[i][j];
        }
    }
}

void moveLeft(vector<vector<int>> &field)
{
    for (int i = 0; i < SIZE; i++)
    {
        vector<bool> canMove(SIZE, true);
        for (int k = 0; k < SIZE; k++)
        {
            for (int j = k; j > 0 && canMove[j - 1]; j--)
            {
                if (field[i][j] == field[i][j - 1] && field[i][j] != 0)
                {
                    field[i][j - 1] *= 2;
                    field[i][j] = 0;
                    canMove[j - 1] = false;
                    break;
                }
                else if (field[i][j - 1] == 0)
                {
                    field[i][j - 1] = field[i][j];
                    field[i][j] = 0;
                }
            }
        }
    }
}

void moveRight(vector<vector<int>> &field)
{
    for (int i = 0; i < SIZE; i++)
    {
        vector<bool> canMove(SIZE, true);
        for (int k = SIZE - 1; k >= 0; k--)
        {
            for (int j = k; j < SIZE - 1 && canMove[j + 1]; j++)
            {
                if (field[i][j] == field[i][j + 1] && field[i][j] != 0)
                {
                    field[i][j + 1] *= 2;
                    field[i][j] = 0;
                    canMove[j + 1] = false;
                    break;
                }
                else if (field[i][j + 1] == 0)
                {
                    field[i][j + 1] = field[i][j];
                    field[i][j] = 0;
                }
            }
        }
    }
}

void moveUp(vector<vector<int>> &field)
{
    for (int j = 0; j < SIZE; j++)
    {
        vector<bool> canMove(SIZE, true);
        for (int k = 0; k < SIZE; k++)
        {
            for (int i = k; i > 0 && canMove[i - 1]; i--)
            {
                if (field[i][j] == field[i - 1][j] && field[i][j] != 0)
                {
                    field[i - 1][j] *= 2;
                    field[i][j] = 0;
                    canMove[i - 1] = false;
                    break;
                }
                else if (field[i - 1][j] == 0)
                {
                    field[i - 1][j] = field[i][j];
                    field[i][j] = 0;
                }
            }
        }
    }
}

void moveDown(vector<vector<int>> &field)
{
    for (int j = 0; j < SIZE; j++)
    {
        vector<bool> canMove(SIZE, true);
        for (int k = SIZE - 1; k >= 0; k--)
        {
            for (int i = k; i < SIZE - 1 && canMove[i + 1]; i++)
            {
                if (field[i][j] == field[i + 1][j] && field[i][j] != 0)
                {
                    field[i + 1][j] *= 2;
                    field[i][j] = 0;
                    canMove[i + 1] = false;
                    break;
                }
                else if (field[i + 1][j] == 0)
                {
                    field[i + 1][j] = field[i][j];
                    field[i][j] = 0;
                }
            }
        }
    }
}

void print(vector<vector<int>> &field)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << field[i][j] << (j == SIZE - 1 ? "\n" : " ");
        }
    }
}

int main()
{
    vector<vector<int>> field(SIZE, vector<int>(SIZE));
    readInput(field);
    int step;
    cin >> step;
    switch (step)
    {
    case 0:
        moveLeft(field);
        break;
    case 1:
        moveUp(field);
        break;
    case 2:
        moveRight(field);
        break;
    case 3:
        moveDown(field);
    }
    print(field);
}

// class Puzzle
// {
//     vector<vector<int>> field;
//     int size = 4;

// public:
//     Puzzle()
//         : field(size, vector<int>(size))
//     {
//     }

//     void readInput()
//     {
//         for (int i = 0; i < size; i++)
//         {
//             for (int j = 0; j < size; j++)
//             {
//                 cin >> field[i][j];
//             }
//         }
//     }

//     void moveLeft()
//     {
//         for (int i = 0; i < size; i++)
//         {
//             vector<bool> canMove(size, true);
//             for (int k = 0; k < size; k++)
//             {
//                 for (int j = k; j > 0 && canMove[j - 1]; j--)
//                 {
//                     if (field[i][j] == field[i][j - 1] && field[i][j] != 0)
//                     {
//                         field[i][j - 1] *= 2;
//                         field[i][j] = 0;
//                         canMove[j - 1] = false;
//                         break;
//                     }
//                     else if (field[i][j - 1] == 0)
//                     {
//                         field[i][j - 1] = field[i][j];
//                         field[i][j] = 0;
//                     }
//                 }
//             }
//         }
//     }

//     void moveRight()
//     {
//         for (int i = 0; i < size; i++)
//         {
//             vector<bool> canMove(size, true);
//             for (int k = size - 1; k >= 0; k--)
//             {
//                 for (int j = k; j < size - 1 && canMove[j + 1]; j++)
//                 {
//                     if (field[i][j] == field[i][j + 1] && field[i][j] != 0)
//                     {
//                         field[i][j + 1] *= 2;
//                         field[i][j] = 0;
//                         canMove[j + 1] = false;
//                         break;
//                     }
//                     else if (field[i][j + 1] == 0)
//                     {
//                         field[i][j + 1] = field[i][j];
//                         field[i][j] = 0;
//                     }
//                 }
//             }
//         }
//     }

//     void moveUp()
//     {
//         for (int j = 0; j < size; j++)
//         {
//             vector<bool> canMove(size, true);
//             for (int k = 0; k < size; k++)
//             {
//                 for (int i = k; i > 0 && canMove[i - 1]; i--)
//                 {
//                     if (field[i][j] == field[i - 1][j] && field[i][j] != 0)
//                     {
//                         field[i - 1][j] *= 2;
//                         field[i][j] = 0;
//                         canMove[i - 1] = false;
//                         break;
//                     }
//                     else if (field[i - 1][j] == 0)
//                     {
//                         field[i - 1][j] = field[i][j];
//                         field[i][j] = 0;
//                     }
//                 }
//             }
//         }
//     }

//     void moveDown()
//     {
//         for (int j = 0; j < size; j++)
//         {
//             vector<bool> canMove(size, true);
//             for (int k = size - 1; k >= 0; k--)
//             {
//                 for (int i = k; i < size - 1 && canMove[i + 1]; i++)
//                 {
//                     if (field[i][j] == field[i + 1][j] && field[i][j] != 0)
//                     {
//                         field[i + 1][j] *= 2;
//                         field[i][j] = 0;
//                         canMove[i + 1] = false;
//                         break;
//                     }
//                     else if (field[i + 1][j] == 0)
//                     {
//                         field[i + 1][j] = field[i][j];
//                         field[i][j] = 0;
//                     }
//                 }
//             }
//         }
//     }

//     void solve(int step)
//     {
//         switch (step)
//         {
//         case 0:
//             moveLeft();
//             break;
//         case 1:
//             moveUp();
//             break;
//         case 2:
//             moveRight();
//             break;
//         case 3:
//             moveDown();
//         }

//         print();
//     }

//     void print()
//     {
//         for (int i = 0; i < size; i++)
//         {
//             for (int j = 0; j < size; j++)
//             {
//                 cout << field[i][j] << (j == size - 1 ? "\n" : " ");
//             }
//         }
//     }
// };