#include <algorithm>
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

void Sudoku::easyMode()
{
	bool needRefresh = true;
	possibleNumber();

	while (needRefresh)
	{
		needRefresh = false;

		// 九宮
		for (int R = 0; R < 9; R += 3)	//大格row
		{
			for (int C = 0; C < 9; C += 3)	//大格col
			{
				for (int n = 1; n <= 9; n++)	//數字1-9
				{
					int canPutNumber = 0;
					bool onlyOnePossible = true;
					int putInNumber = 0;
					int tempR = 0;
					int tempC = 0;
					bool skip = false;

					for (int r = R; r < R + 3; r++)	//九宮小格
					{
						for (int c = C; c < C + 3; c++)
						{
							if (table[r][c] == n + '0')
							{
								skip = true;	//跳過n
								break;
							}
						}
						if (skip)
						{
							break;
						}
					}
					if (skip)	//跳過n
					{
						continue;
					}


					for (int r = R; r < R + 3; r++)	//九宮小格
					{
						for (int c = C; c < C + 3; c++)
						{
							if (record[r][c].size() == 1)	//可能性只有一種
							{
								onlyOnePossible = true;
								putInNumber = record[r][c][0];
								tempR = r;
								tempC = c;
								break;
							}
						}
						if (onlyOnePossible)
						{
							break;
						}
					}

					if (onlyOnePossible)
					{
						needRefresh = true;
						table[tempR][tempC] = putInNumber + '0';
						record[tempR][tempC].clear();
						removeRecord(tempR, tempC, putInNumber);
						continue;
					}

					for (int r = R; r < R + 3; r++)	//九宮小格
					{
						for (int c = C; c < C + 3; c++)
						{
							for (int i = 0; i < record[r][c].size(); i++)	//record裡面有數字n
							{
								if (record[r][c][i] == n)
								{
									canPutNumber++;
									tempR = r;
									tempC = c;
									break;
								}
							}
							if (canPutNumber > 1)
							{
								break;
							}
						}
					}

					if (canPutNumber == 1)//如果可以被放n的只有這格
					{
						needRefresh = true;
						table[tempR][tempC] = n + '0';
						record[tempR][tempC].clear();
						removeRecord(tempR, tempC, n);
					}
				}
			}
		}

		// 直排
		for (int C = 0; C < 9; ++C)
		{
			for (int n = 1; n <= 9; ++n)
			{
				int possiblePosMount = 0;
				int tempR = 0;
				int tempC = 0;

				for (int R = 0; R < 9; ++R)
				{
					auto it = find(record[R][C].begin(), record[R][C].end(), n);
					if (it != record[R][C].end())
					{
						++possiblePosMount;
						tempR = R;
						tempC = C;
					}

					if (possiblePosMount > 1)
					{
						break;
					}
				}

				if (possiblePosMount == 1)
				{
					needRefresh = true;
					table[tempR][tempC] = n;
					record[tempR][tempC].clear();
					removeRecord(tempR, tempC, n);
				}
			}
		}

		// 橫排
		for (int R = 0; R < 9; ++R)
		{
			for (int n = 1; n <= 9; ++n)
			{
				int possiblePosMount = 0;
				int tempR = 0;
				int tempC = 0;

				for (int C = 0; C < 9; ++C)
				{
					auto it = find(record[R][C].begin(), record[R][C].end(), n);
					if (it != record[R][C].end())
					{
						++possiblePosMount;
						tempR = R;
						tempC = C;
					}

					if (possiblePosMount > 1)
					{
						break;
					}
				}

				if (possiblePosMount == 1)
				{
					needRefresh = true;
					table[tempR][tempC] = n;
					record[tempR][tempC].clear();
					removeRecord(tempR, tempC, n);
				}
			}
		}
	}
}

void Sudoku::possibleNumber()
{
}

void Sudoku::removeRecord(int y, int x, int number)
{
	// 3x3 Big Grid
	int beginY = (y / 3) * 3;
	int beginX = (x / 3) * 3;
	for (int i = 0; i < 9; ++i)
	{
		int gridY = beginY + i / 3;
		int gridX = beginX + i % 3;

		if (gridY == y && gridX == x)
		{
			continue;
		}

		record[gridY][gridX].remove(number);
	}

	// Column
	for (int i = 0; i < 9; ++i)
	{
		if (i == y)
		{
			continue;
		}

		record[i][x].remove(number);
	}

	// Row
	for (int i = 0; i < 9; ++i)
	{
		if (i == x)
		{
			continue;
		}

		record[y][i].remove(number);
	}
}
