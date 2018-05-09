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
