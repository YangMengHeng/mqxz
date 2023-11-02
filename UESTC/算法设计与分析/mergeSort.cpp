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
算法问题：实现二路归并排序算法
*/

#define MAXARRAYBUFFER     10000
#define MAXARRAYNUMBER     10000

// array是生成数组的首地址，该函数根据nums大小生成1-maxNumber范围内的随机数数组（有重复数字）
int generateLargeRandArray(int *array, int nums = MAXARRAYBUFFER, int maxNumber = MAXARRAYNUMBER);
void timeTest(int array[], int arrayLen);
void swap(int &x, int &y);
void merge(int array[], int low, int mid, int high);
void mergeSort(int array[], int low, int high);

int main(void)
{
	int inputArray[MAXARRAYBUFFER] = {0};

	srand((unsigned)time(NULL));
	generateLargeRandArray(inputArray);
	timeTest(inputArray, MAXARRAYBUFFER);

	return 0;
}

void timeTest(int array[], int arrayLen)
{
	clock_t startTime, endTime;

	startTime = clock();
	cout << "start:" << startTime << endl;
	mergeSort(array, 0, arrayLen - 1);
	endTime = clock();
	cout << "end  :" << endTime << endl;
	cout << "time :" << ((double)(endTime - startTime) / CLOCKS_PER_SEC) << endl;
}

int generateLargeRandArray(int *array, int nums, int maxNumber)
{
	int len = 0;

	for(int i = 0; i < nums; i++)
	{
		int n = 1 + rand() % maxNumber;
		array[len++] = n;
	}

	return len;
}

void swap(int &x, int &y)
{
	int t = x;
	x = y;
	x = t;
}

void merge(int array[], int low, int mid, int high)
{
	int *tmpArray = (int *)malloc(sizeof(int) * MAXARRAYBUFFER);
	int a = low, b = mid + 1, c = low;

	memcpy(tmpArray, array, sizeof(int) * MAXARRAYBUFFER);

	while(a < (mid + 1) && b < (high + 1))
		if(tmpArray[a] > tmpArray[b])
			array[c++] = tmpArray[b++];
		else
			array[c++] = tmpArray[a++];

	while(a < (mid + 1))
		array[c++] = tmpArray[a++];
	while(b < (high + 1))
		array[c++] = tmpArray[b++];

	free(tmpArray);
}

void mergeSort(int array[], int low, int high)
{
	if(low < high)
	{
		int mid = (low + high) / 2;
		mergeSort(array, low, mid);
		mergeSort(array, mid + 1, high);
		merge(array, low, mid, high);
	}
}