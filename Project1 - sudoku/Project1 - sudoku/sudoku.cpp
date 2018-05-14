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
	//bool needRefresh = true;
	//vector<int>record[N][N];	//�C�@��i�઺�Ʀr
	//possibleNumber(record);

	//while (needRefresh)
	//{
	//	needRefresh = false;

	//	for (int R = 0; R < 9; R += 3)	//�j��row
	//	{
	//		for (int C = 0; C < 9; C += 3)	//�j��col
	//		{
	//			for (int n = 1; n <= 9; n++)	//�Ʀr1-9
	//			{
	//				int canPutNumber = 0;
	//				bool onlyOnePossible = true;
	//				int putInNumber = 0;
	//				int tempR = 0;
	//				int tempC = 0;
	//				bool skip = false;

	//				for (int r = R; r < R + 3; r++)	//�E�c�p��
	//				{
	//					for (int c = C; c < C + 3; c++)
	//					{
	//						if (table[r][c] == n + '0')
	//						{
	//							skip = true;	//���Ln
	//							break;
	//						}
	//					}
	//					if (skip)
	//					{
	//						break;
	//					}
	//				}
	//				if (skip)	//���Ln
	//				{
	//					continue;
	//				}


	//				for (int r = R; r < R + 3; r++)	//�E�c�p��
	//				{
	//					for (int c = C; c < C + 3; c++)
	//					{
	//						if (record[r][c].size() == 1)	//�i��ʥu���@��
	//						{
	//							onlyOnePossible = true;
	//							putInNumber = record[r][c][0];
	//							tempR = r;
	//							tempC = c;
	//							break;
	//						}
	//					}
	//					if (onlyOnePossible)
	//					{
	//						break;
	//					}
	//				}

	//				if (onlyOnePossible)
	//				{
	//					table[tempR][tempC] = putInNumber + '0';
	//					record[tempR][tempC].clear();
	//					needRefresh = true;
	//					// ���O���p�檺��C�p���P���ơB��ơB�E�c �̪��Ҧ��p�檺 i ���i��� remove
	//					continue;
	//				}

	//				for (int r = R; r < R + 3; r++)	//�E�c�p��
	//				{
	//					for (int c = C; c < C + 3; c++)
	//					{
	//						for (int i = 0; i < record[r][c].size(); i++)	//record�̭����Ʀrn
	//						{
	//							if (record[r][c][i] == n)
	//							{
	//								canPutNumber++;
	//								tempR = r;
	//								tempC = c;
	//								break;
	//							}
	//						}
	//						if (canPutNumber > 1)
	//						{
	//							break;
	//						}
	//					}
	//				}

	//				if (canPutNumber == 1)//�p�G�i�H�Q��n���u���o��
	//				{
	//					// ���O���p�檺��C�p���P���ơB��ơB�E�c �̪��Ҧ��p�檺 i ���i��� remove
	//					table[tempR][tempC] = n + '0';
	//					record[tempR][tempC].clear();
	//					needRefresh = true;
	//				}

	//			}
	//		}

	//	}

	//}
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
	for (int gridY = 0; gridY < N / 3; ++gridY)						// �H3���j��� Y
	{
		for (int gridX = 0; gridX < N / 3; ++gridX)					// �H3���j��� X
		{
			for (int y = gridY * 3; y < (gridY + 1) * 3; ++y)		// ��@�E�c�椤�� y �j��
			{
				for (int x = gridX * 3; x < (gridX + 1) * 3; ++x)	// ��@�E�c�椤�� x �j��
				{
					if (table[y][x] != 'n')
					{
						int deleteNum = table[y][x] - 48;
						for (int delY = gridY * 3; delY < (gridY + 1) * 3; ++delY)		// ��@�E�c�椤�� y �j��
						{
							for (int delX = gridX * 3; delX < (gridX + 1) * 3; ++delX)	// ��@�E�c�椤�� x �j��
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