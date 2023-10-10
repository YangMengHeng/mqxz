#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "util.h"

int writeFileWithData(char *fileName, char *data, char *mode)
{
    FILE *file;

    file = fopen(fileName, mode);
    if (file == NULL)
    {
        printf("open file error\n");
        return -1;
    }
    if (fputs(data, file) == EOF)
    {
        printf("write file error\n");
        return -1;
    }
    fclose(file);

    return 0;
}

char numToChar(const int num)
{
    char nData = 0;

    if (num >= 10)
        nData = num - 10 + 'a';
    else if (num < 10 && num >= 0)
        nData = num + '0';
    else
        return -1;

    return nData;
}

int charToNum(const char ch)
{
    int nData = -1;

    if (ch >= '0' && ch <= '9')
        nData = ch - '0';
    else if (ch >= 'a' && ch <= 'f')
        nData = (ch - 'a') + 10;
    else if (ch >= 'A' && ch <= 'F')
        nData = (ch - 'A') + 10;

    return nData;
}

int oneByteToTwoChars(unsigned char *dataIn, unsigned int dataLen, unsigned char *dataOut, unsigned int *dataOutLen)
{
    unsigned int first;
    unsigned int second;
    unsigned int tmp;
    unsigned int index = 0;

    for(int i = 0; i < dataLen; i++)
    {
        tmp = dataIn[i];
        first = tmp >> 4;
        second = tmp & 15;
        dataOut[index++] = numToChar((int)first);
        dataOut[index++] = numToChar((int)second);
    }

    *dataOutLen = index;

    return 0;
}

int twoCharsToOneByte(unsigned char *dataIn, unsigned int dataLen, unsigned char *dataOut, unsigned int *dataOutLen)
{
    int first;
    int second;
    int index = 0;
    unsigned char tmp;
    unsigned char *dataTmp = (dataLen % 2) ? malloc(dataLen + 2) : malloc(dataLen + 1);

    memset(dataTmp, 0, sizeof((char *)dataTmp));
    memcpy(dataTmp, dataIn, dataLen);
    if(dataLen % 2 != 0)
    {
        tmp = dataTmp[dataLen - 1];
        dataTmp[dataLen - 1] = '0';
        dataTmp[dataLen] = tmp;
        dataLen++;
    }

    for(int i = 0; i < dataLen; i += 2)
    {
        first = charToNum((char)dataTmp[i]);
        second = charToNum((char)dataTmp[i + 1]);
        if(first == -1 || second == -1)
            return -1;
        dataOut[index++] = first * 16 + second;
    }

    *dataOutLen = index;

    return 0;
}

int writeToFileWithCharArray(unsigned char *fileName, unsigned char *data, unsigned int dataLen, unsigned int mode)
{
    unsigned int m = BYTETOCHAR;
    unsigned char *dataTmp = NULL;
    unsigned int dataTmpLen = 0;
    int ret = -1;

    if(fileName == NULL || data == NULL || dataLen <= 0)
        return -1;

    if(mode != BYTETOCHAR)
        m = mode;

    dataTmp = malloc(dataLen * 2 + 2);
    if(dataTmp == NULL)
        return -1;

    switch (m)
    {
        case BYTETOCHAR:
            ret = oneByteToTwoChars(data, dataLen, dataTmp, &dataTmpLen);
            RET(ret);
            printf("outlen : %d\n", dataTmpLen);
            for(int i = 1; i <= dataTmpLen; i++)
            {
                printf("%c ", dataTmp[i - 1]);
                if(i % 32 == 0)
                    printf("\n");
            }
            printf("\n");
            break;
        case CHARTOBYTE:
            ret = twoCharsToOneByte(data, dataLen, dataTmp, &dataTmpLen);
            RET(ret);
            printf("outLen : %d\n", dataTmpLen);
            for(int i = 1; i <= dataTmpLen; i++)
            {
                printf("%02x ", dataTmp[i - 1]);
                if(i % 32 == 0)
                    printf("\n");
            }
            printf("\n");
            break;
        default:
            return -1;
    }

    ret = writeFileWithData((char *)fileName, (char *)dataTmp, "w");
    RET(ret);

    return 0;
}

//unsigned char t[256] = "0bd";
//unsigned char f1[256] = "1.txt";
//unsigned char f2[256] = "2.txt";
//unsigned char out[256] = { 0 };
//unsigned char out2[256] = { 0 };
//unsigned int outlen = 0;
//unsigned int out2len = 0;
//
//writeToFileWithCharArray(f2, t, strlen(t), BYTETOCHAR);