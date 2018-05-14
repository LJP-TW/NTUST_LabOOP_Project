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

void Sudoku::solve()
{
	// 先填入 100% 正確的數字後, 再行暴力破解
	easyMode();
	solveBruteForce();
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
								putInNumber = record[r][c].front();
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
							auto it = find(record[R][C].begin(), record[R][C].end(), n);
							if (it != record[R][C].end())
							{
								canPutNumber++;
								tempR = r;
								tempC = c;
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
				int canPutNumber = 0;
				int tempR = 0;
				int tempC = 0;

				for (int R = 0; R < 9; ++R)
				{
					auto it = find(record[R][C].begin(), record[R][C].end(), n);
					if (it != record[R][C].end())
					{
						++canPutNumber;
						tempR = R;
						tempC = C;
					}

					if (canPutNumber > 1)
					{
						break;
					}
				}

				if (canPutNumber == 1)
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
				int canPutNumber = 0;
				int tempR = 0;
				int tempC = 0;

				for (int C = 0; C < 9; ++C)
				{
					auto it = find(record[R][C].begin(), record[R][C].end(), n);
					if (it != record[R][C].end())
					{
						++canPutNumber;
						tempR = R;
						tempC = C;
					}

					if (canPutNumber > 1)
					{
						break;
					}
				}

				if (canPutNumber == 1)
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

void Sudoku::possibleNumber()
{
	// insert possible number 1-9
	for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			if (table[y][x] == 'n')
			{
				for (int i = 1; i <= N; i++)
				{
					record[y][x].push_back(i);
				}
			}
		}
	}

	// 3x3 Big Grid
	for (int gridY = 0; gridY < N / 3; ++gridY)						// 以3為大單位 Y
	{
		for (int gridX = 0; gridX < N / 3; ++gridX)					// 以3為大單位 X
		{
			for (int y = gridY * 3; y < (gridY + 1) * 3; ++y)		// 單一九宮格中的 y 迴圈
			{
				for (int x = gridX * 3; x < (gridX + 1) * 3; ++x)	// 單一九宮格中的 x 迴圈
				{
					if (table[y][x] != 'n')
					{
						int deleteNum = table[y][x] - 48;
						for (int delY = gridY * 3; delY < (gridY + 1) * 3; ++delY)		// 單一九宮格中的 y 迴圈
						{
							for (int delX = gridX * 3; delX < (gridX + 1) * 3; ++delX)	// 單一九宮格中的 x 迴圈
							{
								list<int>::iterator findIter = find(record[delY][delX].begin(), record[delY][delX].end(), deleteNum);
								if (findIter != record[delY][delX].end())
								{
									record[delY][delX].erase(findIter);
								}
							}
						}
					}
				}
			}
		}
	}

	// Column
	for (int x = 0; x < N; ++x)
	{
		for (int y = 0; y < N; ++y)
		{
			if (table[y][x] != 'n')
			{
				for (int i = 0; i < N; ++i)
				{
					int deleteNum = table[y][x] - 48;
					list<int>::iterator findIter = find(record[i][x].begin(), record[i][x].end(), deleteNum);
					if (findIter != record[i][x].end())
					{
						record[i][x].erase(findIter);
					}
				}
			}
		}
	}

	// Row
	for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			if (table[y][x] != 'n')
			{
				for (int i = 0; i < N; ++i)
				{
					int deleteNum = table[y][x] - 48;
					list<int>::iterator findIter = find(record[y][i].begin(), record[y][i].end(), deleteNum);
					if (findIter != record[y][i].end())
					{
						record[y][i].erase(findIter);
					}
				}
			}
		}
	}
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