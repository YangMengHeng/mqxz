#ifndef UTIL_H
#define UTIL_H

#define BYTETOCHAR 1
#define CHARTOBYTE 2

#define RET(x)              \
        if(x)               \
            return x;       \

int writeFileWithData(char *fileName, char *data, char *mode);

char numToChar(const int num);

int charToNum(const char ch);

int oneByteToTwoChars(unsigned char *dataIn, unsigned int dataLen, unsigned char *dataOut, unsigned int *dataOutLen);

int twoCharsToOneByte(unsigned char *dataIn, unsigned int dataLen, unsigned char *dataOut, unsigned int *dataOutLen);

int writeToFileWithCharArray(unsigned char *fileName, unsigned char *data, unsigned int dataLen, unsigned int mode);

#endif //UTIL_H
