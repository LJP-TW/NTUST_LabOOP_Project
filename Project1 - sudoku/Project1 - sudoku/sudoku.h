#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <string>
#define N 9

using namespace std;

class Sudoku
{
public:
	// Default Constructor : �}�@�ӪŪ��ƿW
	Sudoku();
	
	// Constructor : �q filename Ū�J�ƿW�D��
	Sudoku(string filename);

	// �ѼƿW
	//void solve();

	// �ɤO��
	void solveBruteForce();

	// �^�ǼƿW��
	char (&getTable(void))[9][9] { return table; };

private:
	// �ƿW��
	char table[N][N];

	// Helper Function
	// solveBruteForce
	bool solveBruteForceHelper(int y, int x);
	bool isLegal(int y, int x, int number);
};

#endif