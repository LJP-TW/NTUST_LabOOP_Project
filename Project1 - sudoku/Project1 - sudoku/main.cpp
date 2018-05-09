#include <iostream>
#include <fstream>
#include "sudoku.h"
#define N 9


const std::string FILE_NAME = "Question.txt";

void print(char a[N][N]);
char a[N][N] = { 'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n',
'n','n','n','n','n','n','n','n','n' };
int main()
{
	// Read sudoku
	Sudoku s;
	//Sudoku s(FILE_NAME);

	// Solve sudoku
	//s.solve();

	// Output
	print(s.getTable());
	system("pause");
	return 0;
}

// ¦L¥X¯x°}
void print(char a[N][N])
{
	for (int i = 0; i < N; i++)
	{
		printf(" ---------  ---------  ---------\n");
		if (i == 3 || i == 6)
			printf(" ---------  ---------  ---------\n");

		for (int j = 0; j < N; j++)
		{
			if (j == 3 || j == 6)
				printf("¡U");
			printf("¡U%c", a[i][j]);
		}
		printf("¡U\n");
	}
	printf(" ---------  ---------  ---------\n");
}