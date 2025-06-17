#include <iostream>
#include <vector>
using namespace std;

bool isPlacementValid(vector<vector<int>> &grid, int row, int col, int num,
                      vector<int> &rowMask, vector<int> &colMask, vector<int> &boxMask)
{
    int boxIndex = (row / 3) * 3 + (col / 3);
    return !(rowMask[row] & (1 << num)) &&
           !(colMask[col] & (1 << num)) &&
           !(boxMask[boxIndex] & (1 << num));
}

bool solveSudokuRecursive(vector<vector<int>> &grid, int row, int col,
                          vector<int> &rowMask, vector<int> &colMask, vector<int> &boxMask)
{
    int n = grid.size();
    if (row == n - 1 && col == n)
        return true;
    if (col == n)
    {
        row++;
        col = 0;
    }
    if (grid[row][col] != 0)
        return solveSudokuRecursive(grid, row, col + 1, rowMask, colMask, boxMask);

    for (int num = 1; num <= n; num++)
    {
        if (isPlacementValid(grid, row, col, num, rowMask, colMask, boxMask))
        {
            grid[row][col] = num;
            rowMask[row] |= (1 << num);
            colMask[col] |= (1 << num);
            boxMask[(row / 3) * 3 + (col / 3)] |= (1 << num);

            if (solveSudokuRecursive(grid, row, col + 1, rowMask, colMask, boxMask))
                return true;

            grid[row][col] = 0;
            rowMask[row] &= ~(1 << num);
            colMask[col] &= ~(1 << num);
            boxMask[(row / 3) * 3 + (col / 3)] &= ~(1 << num);
        }
    }
    return false;
}

void solveSudoku(vector<vector<int>> &grid)
{
    int n = grid.size();
    vector<int> rowMask(n, 0), colMask(n, 0), boxMask(n, 0);

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            int num = grid[row][col];
            if (num != 0)
            {
                rowMask[row] |= (1 << num);
                colMask[col] |= (1 << num);
                boxMask[(row / 3) * 3 + (col / 3)] |= (1 << num);
            }
        }
    }

    solveSudokuRecursive(grid, 0, 0, rowMask, colMask, boxMask);
}

int main()
{
    vector<vector<int>> sudokuGrid = {
        {0, 0, 0, 2, 6, 0, 7, 0, 1},
        {6, 8, 0, 0, 7, 0, 0, 9, 0},
        {1, 9, 0, 0, 0, 4, 5, 0, 0},
        {8, 2, 0, 1, 0, 0, 0, 4, 0},
        {0, 0, 4, 6, 0, 2, 9, 0, 0},
        {0, 5, 0, 0, 0, 3, 0, 2, 8},
        {0, 0, 9, 3, 0, 0, 0, 7, 4},
        {0, 4, 0, 0, 5, 0, 0, 3, 6},
        {7, 0, 3, 0, 1, 8, 0, 0, 0}};

    solveSudoku(sudokuGrid);

    for (int row = 0; row < sudokuGrid.size(); row++)
    {
        for (int col = 0; col < sudokuGrid[row].size(); col++)
        {
            cout << sudokuGrid[row][col] << " ";
        }
        cout << endl;
    }

    return 0;
}
