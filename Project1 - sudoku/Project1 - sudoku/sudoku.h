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
	//void solve();

	// 建立可能性 record
	void possibleNumber();

	// 消除與(x, y)同 九宮 直排 橫排 的 number 可能性
	void removeRecord(int y, int x, int number);

	// easyMode : 100% 能填入才填入
	void easyMode();

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
	// solveBruteForce
	bool isLegal(int y, int x, int number);
	coordinate nextBlank(int y, int x);
};

#endif
