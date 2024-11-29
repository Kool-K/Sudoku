#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
void displayGrid(vector<vector<int>> &grid)
{
    for (int i = 0; i < 4; i++)
    {
        if (i == 2)
        {
            cout << "---------" << endl;
        }
        for (int j = 0; j < 4; ++j)
        {
            if (j == 2)
            {
                cout << "| ";
            }
            if (grid[i][j] == 0)
                cout << ". ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValid(vector<vector<int>> &grid, int row, int col, int num)
{
    // checks if the no entered is valid as in distinct to the row and column along with the 2x2 block
    for (int i = 0; i < 4; i++)
    {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    int startRow = (row / 2) * 2;
    int startCol = (col / 2) * 2;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}

// Backtracking function to generate the board
bool generateBoard(vector<vector<int>> &grid)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (grid[row][col] == 0)
            {
                // Try placing each number from 1 to 4
                for (int num = 1; num <= 4; num++)
                {
                    if (isValid(grid, row, col, num))
                    {
                        grid[row][col] = num;
                        if (generateBoard(grid))
                        {
                            return true;
                        }
                        grid[row][col] = 0; // Backtrack
                    }
                }
                return false; // No valid number can be placed
            }
        }
    }
    return true; // All cells are filled
}

// removing numbers from the grid
void removeNumbers(vector<vector<int>> &grid, int totalToRemove)
{
    int removed = 0;
    while (removed < totalToRemove)
    {
        int row = rand() % 4;
        int col = rand() % 4;
        if (grid[row][col] != 0)
        {
            grid[row][col] = 0;
            removed++;
        }
    }
}

void play(vector<vector<int>> &grid)
{
    int row, col, num;

    while (true)
    {
        cout << "Current Puzzle:" << endl;
        displayGrid(grid);

        cout << "Enter your move (row, column, number) or press -1 to exit: ";
        cin >> row;

        if (row == -1)
        {
            cout << "Exiting game!" << endl;
            break;
        }

        cin >> col >> num;

        // Checking validity
        if (row >= 1 && row <= 4 && col >= 1 && col <= 4 && num >= 1 && num <= 4)
        {
            row--;
            col--; // for 0-based indexing

            if (grid[row][col] == 0)
            {
                if (isValid(grid, row, col, num))
                {
                    grid[row][col] = num;
                    cout << "VALUE ENTERED!" << endl;
                }
                else
                {
                    cout << "There is some repetition, try again." << endl;
                }
            }
            else
            {
                cout << "Cell already filled, try another." << endl;
            }
        }
        else
        {
            cout << "Invalid input, enter a valid row (1-4), column (1-4), and number (1-4) for the entry." << endl;
        }

        // Check if the game is over
        bool solved = true;
        for (int i = 0; i < 4 && solved; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (grid[i][j] == 0)
                {
                    solved = false;
                    break;
                }
            }
        }

        if (solved)
        {
            cout << "Congratulations, you solved it!" << endl;
            cout << "Final board is:" << endl;
            displayGrid(grid);
            break;
        }
    }
}

int main()
{
    srand(time(0));

    vector<vector<int>> grid(4, vector<int>(4, 0));

    generateBoard(grid);

    // Removing 10 numbers, leaving 6 for the user for solving
    removeNumbers(grid, 10);

    cout << "Solve the puzzle fill values in the regions marked with a '.':" << endl;
    play(grid);

    return 0;
}
