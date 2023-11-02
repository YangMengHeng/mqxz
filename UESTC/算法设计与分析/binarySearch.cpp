#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <istream>
using namespace std;

/*
算法问题：二分搜索算法
问题描述：
	设a[0:n-1]是已经排好序的数组，请改写二分搜索算法，使得：
	当搜索元素x不在数组中时，返回小于x的最大元素位置i和大于x的最小元素位置j
	当搜索元素x在数组中时，返回元素x在数组中的位置
输入：
	第一行为数组的长度，当第一行输入为0时表示数据输入结束，
	第二行为数组数据，
	第三行为要查找的元素
输出：
	若搜索元素在数组中不存在，则第四行输出小于x的最大元素位置i和大于x的最小元素位置j（若没有大于x的最小元素或小于x的最大元素则输出-1）
	若搜索元素在数组中存在，则输出元素x在数组中的位置
样例输入：
	3
	1 2 3
	4
	5
	1 3 4 6 10
	6
样例输出：
	2 -1
	3
*/

#define MAXARRAYNUMBER 1024

void binarySearch(int *array, int len, int value, int *res);

int main(void)
{
	int inputLen = 0, searchValue = 0;
	int result[2] = { -2, -2 };
	int inputArray[MAXARRAYNUMBER] = {0};

	while (cin >> inputLen)
	{
		if(!inputLen)
			break;
		for(int i = 0; i < inputLen; i++)
			cin >> inputArray[i];
		cin >> searchValue;
		binarySearch(inputArray, inputLen, searchValue, result);
		for(int i = 0; i < 2; i++)
			if(result[i] != -2)
				cout << result[i] << ' ';
		cout << endl;
		for (int i = 0; i < 2; i++)
			result[i] = -2;
	}

	return 0;
}

void binarySearch(int* array, int len, int value, int* res)
{
	int mid = len / 2, left = 0, right = len - 1;
	int i = mid, j = mid;

	while(left <= right)
	{
		if(value > array[mid])
		{
			left = mid + 1;
			if(left > len - 1)
			{
				i = right;
				j = -1;
			}
			else
				i = mid;
		}
		else if(value < array[mid])
		{
			right = mid - 1;
			if (right < 0)
			{
				i = -1;
				j = left;
			}
			else
				j = mid;
		}
		else
		{
			res[0] = mid;
			return ;
		}
		mid = (left + right) / 2;
	}

	res[0] = i;
	res[1] = j;
}