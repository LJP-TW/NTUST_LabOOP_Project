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
	// Default Constructor : 開一個空的數獨
	Sudoku();

	// Constructor : 從 filename 讀入數獨題目
	Sudoku(string filename);

	// 解數獨
	//void solve();

	// 建立可能性 record
	void possibleNumber(vector<int>(&record)[N][N]);

	// 消除同 九宮 直排 橫排 的特定可能性
	//void removeRecord();

	// easyMode : 100% 能填入才填入
	void easyMode();

	// 回傳數獨表
	char(&getTable(void))[9][9]{ return table; };

private:
	// 數獨表
	char table[N][N];
};

#endif
