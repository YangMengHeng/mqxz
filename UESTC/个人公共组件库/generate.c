#include <stdlib.h>

#define MAXARRAYNUMBER 1024 // 数组元素最大值
#define MAXARRAYBUFFER 1024 // 数组最大元素数量

/*
 * name:生成随机数组
 * author:万俟修竹
 * parameters:
 * [output] array       生成的随机元素存到array地址
 * [input]  nums        待生成元素的数量
 * [input]  maxNumber   待生成元素的最大值
 * */
int generateLargeRandArray(int *array, int nums = MAXARRAYBUFFER, int maxNumber = MAXARRAYNUMBER);

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