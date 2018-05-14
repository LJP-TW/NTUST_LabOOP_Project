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

		// �E�c
		for (int R = 0; R < 9; R += 3)	//�j��row
		{
			for (int C = 0; C < 9; C += 3)	//�j��col
			{
				for (int n = 1; n <= 9; n++)	//�Ʀr1-9
				{
					int canPutNumber = 0;
					bool onlyOnePossible = true;
					int putInNumber = 0;
					int tempR = 0;
					int tempC = 0;
					bool skip = false;

					for (int r = R; r < R + 3; r++)	//�E�c�p��
					{
						for (int c = C; c < C + 3; c++)
						{
							if (table[r][c] == n + '0')
							{
								skip = true;	//���Ln
								break;
							}
						}
						if (skip)
						{
							break;
						}
					}
					if (skip)	//���Ln
					{
						continue;
					}


					for (int r = R; r < R + 3; r++)	//�E�c�p��
					{
						for (int c = C; c < C + 3; c++)
						{
							if (record[r][c].size() == 1)	//�i��ʥu���@��
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

					for (int r = R; r < R + 3; r++)	//�E�c�p��
					{
						for (int c = C; c < C + 3; c++)
						{
							for (int i = 0; i < record[r][c].size(); i++)	//record�̭����Ʀrn
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

					if (canPutNumber == 1)//�p�G�i�H�Q��n���u���o��
					{
						needRefresh = true;
						table[tempR][tempC] = n + '0';
						record[tempR][tempC].clear();
						removeRecord(tempR, tempC, n);
					}
				}
			}
		}

		// ����
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

		// ���
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
