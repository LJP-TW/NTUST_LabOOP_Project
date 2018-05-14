#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <string>
#include <stack>
#define N 9

using namespace std;

struct coordinate
{

	int x;
	int y;
};

class Sudoku
{
public:
	// Default Constructor : 秨计縒
	Sudoku();
	
	// Constructor : 眖 filename 弄计縒肈ヘ
	Sudoku(string filename);

	// 秆计縒
	//void solve();

	// 忌秆
	void solveBruteForce();

	// 肚计縒
	char (&getTable(void))[9][9] { return table; };

private:
	// 计縒
	char table[N][N];

	// Helper Function
	// solveBruteForce
	bool isLegal(int y, int x, int number);
	coordinate nextBlank(int y, int x);
};

#endif