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
	vector<int>record[N][N];	//每一格可能的數字
	possibleNumber(record);

	while (needRefresh)
	{
		needRefresh = false;

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
						table[tempR][tempC] = putInNumber + '0';
						record[tempR][tempC].clear();
						needRefresh = true;
						// 把跟記錄小格的文青小物同直排、橫排、九宮 裡的所有小格的 i 的可能性 remove
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
						// 把跟記錄小格的文青小物同直排、橫排、九宮 裡的所有小格的 i 的可能性 remove
						table[tempR][tempC] = n + '0';
						record[tempR][tempC].clear();
						needRefresh = true;
					}

				}
			}

		}

	}
}

void Sudoku::possibleNumber()
{
}