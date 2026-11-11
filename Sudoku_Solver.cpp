#include <iostream>
using namespace std;

// Check whether a number can be placed in the given cell.
bool isSafe(int grid[9][9], int row, int col, int num) {
    // Check the row.
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check the column.
    for (int x = 0; x < 9; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid.
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Solve the Sudoku puzzle using backtracking.
bool solveSudoku(int grid[9][9]) {
    int row = -1;
    int col = -1;
    bool empty = false;

    // Find an empty cell (represented by 0).
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                empty = true;
                break;
            }
        }

        if (empty) {
            break;
        }
    }

    // No empty cells means the puzzle is solved.
    if (!empty) {
        return true;
    }

    // Try numbers from 1 to 9.
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            // Undo the choice and try another number.
            grid[row][col] = 0;
        }
    }

    return false;
}

// Display the Sudoku grid.
void printGrid(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
}

int main() {
    int grid[9][9];

    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> grid[i][j];
        }
    }

    cout << "\nSudoku Puzzle:\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for this Sudoku puzzle.\n";
    }

    return 0;
}
