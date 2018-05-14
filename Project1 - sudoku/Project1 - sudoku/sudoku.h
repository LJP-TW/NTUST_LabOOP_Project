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
	// Default Constructor : �}�@�ӪŪ��ƿW
	Sudoku();

	// Constructor : �q filename Ū�J�ƿW�D��
	Sudoku(string filename);

	// �ѼƿW
	//void solve();

	//
	void possibleNumber(vector<int>(&record)[9][9]);

	//
	void removeRecord();

	//easyMode
	void easyMode();

	// �^�ǼƿW��
	char(&getTable(void))[9][9]{ return table; };

private:
	// �ƿW��
	char table[N][N];
};

#endif
