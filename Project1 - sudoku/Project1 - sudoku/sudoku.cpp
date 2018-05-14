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
	vector<int>record[N][N];	//�C�@��i�઺�Ʀr
	possibleNumber(record);

	while (needRefresh)
	{
		needRefresh = false;

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
						table[tempR][tempC] = putInNumber + '0';
						record[tempR][tempC].clear();
						needRefresh = true;
						// ���O���p�檺��C�p���P���ơB��ơB�E�c �̪��Ҧ��p�檺 i ���i��� remove
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
						// ���O���p�檺��C�p���P���ơB��ơB�E�c �̪��Ҧ��p�檺 i ���i��� remove
						table[tempR][tempC] = n + '0';
						record[tempR][tempC].clear();
						needRefresh = true;
					}

				}
			}

		}

	}
}

void Sudoku::possibleNumber(vector<int>(&record)[N][N])
{
	bool isInRow = false;
	bool isInCol = false;


	for (int r = 0; r < 9; r++)	//�P�_row
	{
		for (int i = 1; i < 10; i++)	//�Ʀr1-9
		{
			for (int c = 0; c < 9; c++)	//�����col�ݦ��S���X�{�Mi�ۦP���Ʀr
			{
				if (table[r][c] - '0' == i + '0')
				{
					isInRow = true;
					break;
				}
				if (table[c][r] - '0' == i + '0')
				{
					isInCol = true;
					break;
				}
			}
			if (isInRow == false && isInCol == false)	//�S�X�{�N��Ů泣��i
			{
				for (int c = 0; c < 9; c++)
				{
					if (table[r][c] == 'n')
					{
						record[r][c].push_back(i);
					}
					if (table[c][r] == 'n')
					{
						record[c][r].push_back(i);
					}
				}
			}

		}
	}

}