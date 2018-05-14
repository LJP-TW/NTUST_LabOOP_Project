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
	// Default Constructor : 開一個空的數獨
	Sudoku();

	// Constructor : 從 filename 讀入數獨題目
	Sudoku(string filename);

	// 解數獨
	void solve();

	// 暴力解
	void solveBruteForce();

	// 回傳數獨表
	char(&getTable(void))[9][9]{ return table; };

private:
	// 數獨表
	char table[N][N];
	
	// 可能性表
	list<int> record[N][N];

	// Helper Function
	// solveBruteForce()
	//   - isLegal() : 此 number 是否能填入 (x, y)
	bool isLegal(int y, int x, int number);
	//   - nextBlank() : 搜尋下一個待填處
	coordinate nextBlank(int y, int x);

	// solve()
	//   - easyMode() : 100% 能填入才填入
	void easyMode();
	//       - possibleNumber() : 建立可能性 record
	void possibleNumber();
	//       - removeRecord() : 消除與(x, y)同 九宮 直排 橫排 的 number 可能性
	void removeRecord(int y, int x, int number);

};

#endif
