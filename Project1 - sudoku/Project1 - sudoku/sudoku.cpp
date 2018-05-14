#include "sudoku.h"
//test
Sudoku::Sudoku()
{
	for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			table[y][x] = '0';
		}
	}
}

Sudoku::Sudoku(string filename)
{
	ifstream file(filename);
	for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			file >> table[y][x];
		}
	}
}

void Sudoku::solveBruteForce()
{
	solveBruteForceHelper(0, 0);
}

bool Sudoku::solveBruteForceHelper(int y, int x)
{
	// If this grid already have a number
	if (table[y][x] != 'n')
	{
		// Go ahead to next coordinate
		if (solveBruteForceHelper(y + (x + 1) / 9, (x + 1) % 9))
		{
			return true;
		}
	}
	else
	{
		// Brute Force the number
		for (int num = 1; num <= 9; ++num)
		{
			if (isLegal(y, x, num))
			{
				// Give a legal number to (y, x)
				table[y][x] = num + '0';

				// If y = 8, x = 8, and value is legal, sudoku is solved.
				if (y == 8 && x == 8)
				{
					return true;
				}

				// Go ahead to next coordinate
				if (solveBruteForceHelper(y + (x + 1) / 9, (x + 1) % 9))
				{
					return true;
				}
			}
		}

		// If legal number for this grid doesn't exist
		table[y][x] = 'n';
	}


	return false;
}

bool Sudoku::isLegal(int y, int x, int number)
{
	number += '0';

	// 3x3 Big Grid
	int beginY = (y / 3) * 3;
	int beginX = (x / 3) * 3;
	for (int i = 0; i < 9; ++i)
	{
		int gridY = beginY + i / 3;
		int gridX = beginX + i % 3;

		if (gridY != y && gridX != x && table[gridY][gridX] == number)
		{
			return false;
		}
	}

	// Column
	for (int i = 0; i < 9; ++i)
	{
		if (i != y && table[i][x] == number)
		{
			return false;
		}
	}

	// Row
	for (int i = 0; i < 9; ++i)
	{
		if (i != x && table[y][i] == number)
		{
			return false;
		}
	}

	return true;
}
