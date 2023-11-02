#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <istream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

/*
算法问题：棋盘覆盖算法
*/

#define MAXARRAYBUFFER 170000
#define MAXARRAYNUMBER 170000

int tileIndex = 1;	 // 骨牌序号
int board[128][128]; // 二维数组模拟棋盘
int boardSize = 8;	 // 棋盘边长

void chessBoard(int tr, int tc, int dr, int dc, int size);

int main()
{
	chessBoard(0, 0, 3, 3, boardSize); // (0, 0)为顶点,大小为boardSize的棋盘,特殊方块位于(3, 3)

	cout << endl << endl << endl;
	for(int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
			cout << board[i][j] << '\t';
		cout << endl << endl << endl;
	}
	return 0;
}

// (tr,tc)表示棋盘的左上角坐标(即确定棋盘位置), (dr,dc)表示特殊方块的位置, size=2^k确定棋盘大小
void chessBoard(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
		return;

	int s = size / 2;         // 分割棋盘
	int t = tileIndex++;	  // t记录本层骨牌序号

	// 判断特殊方格在不在左上棋盘
	if (dr < tr + s && dc < tc + s)
		chessBoard(tr, tc, dr, dc, s);
	else
	{
		board[tr + s - 1][tc + s - 1] = t;			   // 用t号的L型骨牌覆盖右下角
		chessBoard(tr, tc, tr + s - 1, tc + s - 1, s); // 递归覆盖其余方格
	}

	// 判断特殊方格在不在右上棋盘
	if (dr < tr + s && dc >= tc + s)
		chessBoard(tr, tc + s, dr, dc, s);
	else
	{
		board[tr + s - 1][tc + s] = t;
		chessBoard(tr, tc + s, tr + s - 1, tc + s, s);
	}

	// 判断特殊方格在不在左下棋盘
	if (dr >= tr + s && dc < tc + s)
		chessBoard(tr + s, tc, dr, dc, s);
	else
	{
		board[tr + s][tc + s - 1] = t;
		chessBoard(tr + s, tc, tr + s, tc + s - 1, s);
	}

	// 判断特殊方格在不在右下棋盘
	if (dr >= tr + s && dc >= tc + s)
		chessBoard(tr + s, tc + s, dr, dc, s);
	else
	{
		board[tr + s][tc + s] = t;
		chessBoard(tr + s, tc + s, tr + s, tc + s, s);
	}
}