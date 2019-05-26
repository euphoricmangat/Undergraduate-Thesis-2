#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <chrono>

#define N 9
#define UNASSIGNED 0

// Timer structure to compute execution time
struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer() {
		start = std::chrono::steady_clock::now();
	}

	~Timer() {
		end = std::chrono::steady_clock::now();
		duration = end - start;

		float sec = duration.count();
		std::cout << "Timer took: " << sec << "s " << std::endl;
	}
};

bool FindUnassignedLocation(int grid[N][N], int &row, int &col);
bool isSafe(int grid[N][N], int row, int col, int num);

// assign values to all unassigned locations for Sudoku solution  
bool SolveSudoku(int grid[N][N])
{
    int row, col;
    if (!FindUnassignedLocation(grid, row, col))
       return true;
    for (int num = 1; num <= 9; num++)
    {
    if (isSafe(grid, row, col, num))
    {
        grid[row][col] = num;
        if (SolveSudoku(grid))
            return true;
        grid[row][col] = UNASSIGNED;
    }
    }
    return false;
}

// Searches the grid to find an entry that is still unassigned.
bool FindUnassignedLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

// Returns whether any assigned entry n the specified row matches the given number.
bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
    return false;
}

// Returns whether any assigned entry in the specified column matches the given number.
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Returns whether any assigned entry within the specified 3x3 box matches the given number.
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

// Returns whether it will be legal to assign num to the given row,col location. 
bool isSafe(int grid[N][N], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
       !UsedInBox(grid, row - row % 3 , col - col % 3, num);
}

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            std::cout<< grid[row][col] << "  ";
        std::cout<< std::endl << "\t";
    }
}

int main()
{
	Timer timer;
    int grid[N][N] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 3, 6, 0, 0, 0, 0, 0},
                      {0, 7, 0, 0, 9, 0, 2, 0, 0},
                      {0, 5, 0, 0, 0, 7, 0, 0, 0},
                      {0, 0, 0, 0, 4, 5, 7, 0, 0},
                      {0, 0, 0, 1, 0, 0, 0, 3, 0},
                      {0, 0, 1, 0, 0, 0, 0, 6, 8},
                      {0, 0, 8, 5, 0, 0, 0, 1, 0},
                      {0, 9, 0, 0, 0, 0, 4, 0, 0}};
	if (SolveSudoku(grid) == true) {
		std::cout << "Sudoko Solved: \n\n\t";
		printGrid(grid);
	}
    else
        std::cout<<"No solution exists"<<std::endl;

	std::cout << std::endl;
    return 0;
}

