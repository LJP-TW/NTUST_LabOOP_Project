#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <iostream>
#include <list>
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

	// �إߥi��� record
	void possibleNumber();

	// �����P �E�c ���� ��� ���S�w�i���
	//void removeRecord();

	// easyMode : 100% ���J�~��J
	void easyMode();

	// �^�ǼƿW��
	char(&getTable(void))[9][9]{ return table; };

private:
	// �ƿW��
	char table[N][N];
	
	// �i��ʪ�
	list<int> record[N][N];
};

#endif
