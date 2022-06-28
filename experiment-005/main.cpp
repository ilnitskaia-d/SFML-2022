#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<int>> puzzle = {{2, 2, 4, 0}, {32, 0, 0, 128}, {0, 0, 0, 4}, {2, 0, 0, 2}};

    for (int step = 0; step < 3; ++step)
    {
        bool isChanged = false;
        vector<vector<bool>> merged(4, vector<bool>(4, true));
        for (int r = 0; r < 4; r++)
        {
            for (int c = 1; c < 4; c++)
            {
                if (puzzle[r][c] != 0 && puzzle[r][c - 1] == 0)
                {
                    puzzle[r][c - 1] = puzzle[r][c];
                    puzzle[r][c] = 0;
                    isChanged = true;
                }
                else if (puzzle[r][c] == puzzle[r][c - 1] && merged[r][c - 1])
                {
                    puzzle[r][c - 1] *= 2;
                    puzzle[r][c] = 0;
                    merged[r][c - 1] = false;
                    isChanged = true;
                }
            }
        }
        if (isChanged)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    cout << puzzle[i][j] << " ";
                }
                cout << endl;
            }
            cout << "---------\n";
        }
    }
}
