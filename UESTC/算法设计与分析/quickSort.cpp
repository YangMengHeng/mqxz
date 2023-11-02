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
算法问题：比较不同的快速排序算法
问题描述：
	请尝试用三者取中法完成快速排序，并编写算法与取第一个元素为枢纽的快速排序方法进行比较测试
	在练习题的基础上增加了采用区间比例取随机元素作为枢纽的快速排序方法进行比较测试
*/

#define MAXARRAYBUFFER 170000
#define MAXARRAYNUMBER 170000
#define THREENUMBERTAKEMID 0 // 三者取中法
#define FIRSTNUMBERTAKEMID 1 // 首元素法
#define RANDNUMBERTAKEMID 2	 // 随机元素法

// array是生成数组的首地址，该函数根据nums大小生成1-maxNumber范围内的随机数数组（有重复数字）
int generateLargeRandArray(int *array, int nums = MAXARRAYBUFFER, int maxNumber = MAXARRAYNUMBER);
void timeTest(int *array, int arrayLen, int index);
void swap(int &x, int &y);
int partition(int sortArray[], int left, int right, int index);
void quickSort(int sortArray[], int left, int right, int index);
int getThreeNumberMid(int array[], int a, int b, int c);

int main(void)
{
	int inputArray1[MAXARRAYBUFFER] = {0};
	int inputArray2[MAXARRAYBUFFER] = {0};
	int inputArray3[MAXARRAYBUFFER] = {0};

	srand((unsigned)time(NULL));
	generateLargeRandArray(inputArray1);
	memcpy(inputArray2, inputArray1, sizeof(inputArray1));
	memcpy(inputArray3, inputArray1, sizeof(inputArray1));

	timeTest(inputArray1, MAXARRAYBUFFER, THREENUMBERTAKEMID);
	timeTest(inputArray2, MAXARRAYBUFFER, FIRSTNUMBERTAKEMID);
	timeTest(inputArray3, MAXARRAYBUFFER, RANDNUMBERTAKEMID);

	return 0;
}

void timeTest(int array[], int arrayLen, int index)
{
	clock_t startTime, endTime;

	startTime = clock();
	cout << "start:" << startTime << endl;
	quickSort(array, 0, arrayLen - 1, index);
	endTime = clock();
	cout << "end  :" << endTime << endl;
	cout << "time :" << ((double)(endTime - startTime) / CLOCKS_PER_SEC) << endl;
}

int generateLargeRandArray(int *array, int nums, int maxNumber)
{
	int len = 0;

	for (int i = 0; i < nums; i++)
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

int getThreeNumberMid(int array[], int a, int b, int c)
{
	if (array[a] > array[b])
	{
		if (array[a] < array[c])
			return array[a];
		else
		{
			if (array[b] >= array[c])
				return array[b];
			else
				return array[c];
		}
	}

	if (array[b] > array[c])
	{
		if (array[b] < array[a])
			return array[b];
		else
		{
			if (array[a] >= array[c])
				return array[a];
			else
				return array[c];
		}
	}

	if (array[c] > array[a])
	{
		if (array[c] < array[b])
			return array[c];
		else
		{
			if (array[b] >= array[a])
				return array[b];
			else
				return array[a];
		}
	}
}

int partition(int sortArray[], int left, int right, int index)
{
	int t, midNumber;

	switch (index)
	{
	case THREENUMBERTAKEMID:
		midNumber = getThreeNumberMid(sortArray, left, (left + right) / 2, right);
		break;
	case FIRSTNUMBERTAKEMID:
		midNumber = sortArray[left];
		break;
	case RANDNUMBERTAKEMID:
		midNumber = (round(1.0 * rand() / RAND_MAX * (right - left) + left));
		swap(sortArray[left], sortArray[midNumber]);
		break;
	default:
		return -1;
	}

	t = sortArray[left];
	while (left < right)
	{
		while (left < right && sortArray[right] >= t)
			right--;
		sortArray[left] = sortArray[right];
		while (left < right && sortArray[left] <= t)
			left++;
		sortArray[right] = sortArray[left];
	}
	sortArray[left] = t;

	return left;
}

void quickSort(int sortArray[], int left, int right, int index)
{
	if (left < right)
	{
		int pos = partition(sortArray, left, right, index);
		quickSort(sortArray, left, pos - 1, index);
		quickSort(sortArray, pos + 1, right, index);
	}
}