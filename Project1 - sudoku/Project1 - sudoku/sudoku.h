#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#define N 9

using namespace std;

class Sudoku
{
public:
	// Default Constructor : 秨计縒
	Sudoku();

	// Constructor : 眖 filename 弄计縒肈ヘ
	Sudoku(string filename);

	// 秆计縒
	//void solve();

	//
	void possibleNumber(vector<int>(&record)[9][9]);

	//
	void removeRecord();

	//easyMode
	void easyMode();

	// 肚计縒
	char(&getTable(void))[9][9]{ return table; };

private:
	// 计縒
	char table[N][N];
};

#endif
