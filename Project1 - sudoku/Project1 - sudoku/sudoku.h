#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <iostream>
#include <list>
#include <string>
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
	// Default Constructor : �}�@�ӪŪ��ƿW
	Sudoku();

	// Constructor : �q filename Ū�J�ƿW�D��
	Sudoku(string filename);

	// �ѼƿW
	void solve();

	// �ɤO��
	void solveBruteForce();

	// �^�ǼƿW��
	char(&getTable(void))[9][9]{ return table; };

private:
	// �ƿW��
	char table[N][N];
	
	// �i��ʪ�
	list<int> record[N][N];

	// Helper Function
	// solveBruteForce()
	//   - isLegal() : �� number �O�_���J (x, y)
	bool isLegal(int y, int x, int number);
	//   - nextBlank() : �j�M�U�@�ӫݶ�B
	coordinate nextBlank(int y, int x);

	// solve()
	//   - easyMode() : 100% ���J�~��J
	void easyMode();
	//       - possibleNumber() : �إߥi��� record
	void possibleNumber();
	//       - removeRecord() : �����P(x, y)�P �E�c ���� ��� �� number �i���
	void removeRecord(int y, int x, int number);

};

#endif
