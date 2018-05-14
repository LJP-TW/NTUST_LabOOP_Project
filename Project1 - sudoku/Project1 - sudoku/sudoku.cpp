#include "sudoku.h"

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
	coordinate completedPos[128];
	int idx = 0;

	coordinate nowPos;

	nowPos = nextBlank(0, -1);

	// If still have next blank
	while (nowPos.y != N)
	{
		// set table[nowPos.y][nowPos.x] to '0' if it isn't number
		if ('0' > table[nowPos.y][nowPos.x] || table[nowPos.y][nowPos.x] > '9')
		{
			table[nowPos.y][nowPos.x] = '0';
		}
		++table[nowPos.y][nowPos.x];

		if (table[nowPos.y][nowPos.x] > '9')
		{
			table[nowPos.y][nowPos.x] = '0';

			// Pop
			nowPos = completedPos[--idx];
		}
		else
		{
			if (isLegal(nowPos.y, nowPos.x, table[nowPos.y][nowPos.x] - '0'))
			{
				// Push
				completedPos[idx++] = nowPos;

				nowPos = nextBlank(nowPos.y, nowPos.x);
			}
		}
	}
}

bool Sudoku::isLegal(int y, int x, int number)
{
	number += '0';

	// 3x3 Big Grid
	int beginY = (y / 3) * 3;
	int beginX = (x / 3) * 3;
	for (int i = 0; i < N; ++i)
	{
		int gridY = beginY + i / 3;
		int gridX = beginX + i % 3;

		if (gridY != y && gridX != x && table[gridY][gridX] == number)
		{
			return false;
		}
	}

	// Column
	for (int i = 0; i < N; ++i)
	{
		if (i != y && table[i][x] == number)
		{
			return false;
		}
	}

	// Row
	for (int i = 0; i < N; ++i)
	{
		if (i != x && table[y][i] == number)
		{
			return false;
		}
	}

	return true;
}

coordinate Sudoku::nextBlank(int y, int x)
{
	coordinate c;
	c.x = x;
	c.y = y;

	while (true)
	{
		++c.x;
		c.y += (c.x / N);
		c.x %= N;

		if (c.y == N)
		{
			break;
		}

		if ('1' > table[c.y][c.x] || table[c.y][c.x] > '9')
		{
			break;
		}
	}

	return c;
}
