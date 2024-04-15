#include <stdio.h>
#include "stdlib.h"
#include "math.h"

int main() {
    printf("Hello, World!\n");
    return 0;
}


bool validateIntNumber(const char *number) {

    unsigned int i = 0;

    while (*(number + i))
        if (*(number + i) < '0' || *(number + i) > '9')
            return false;
        else
            i++;
    return true;

}

unsigned int len(const char *str) {

    unsigned int size = 0;

    while (*(str + size))
        size++;

    return size;
}

char *charDeepCopy(const char *str) {

    char *copy = (char *) malloc(sizeof(char) * len(str));

    for (int i = 0; *(str + i); i++)
        *(copy + i) = *(str + i);

    return copy;

}

char *strToBCD(const char *number) {
//    if (!validateIntNumber(number))
//        printf();
    char *bcd = charDeepCopy(number);

    for (int i = 0; *(bcd + i); i++)
        *(bcd + i) = *(bcd + i) - '0';

    return bcd;

}

bool BCDZeroCheck(const char *bcd, unsigned int size) {

    for (unsigned int ptr = 0; ptr < size; ptr++)
        if (*(bcd + ptr) > 0)
            return false;
    return true;
}

void divideBCDTo10(char *bcd, unsigned int charSize) {
    for (int ptr = (int) charSize - 1; ptr >= 0; ptr--) {
        *(bcd + ptr) >> 1;
        if (*(bcd + ptr - 1) % 2 == 1 && (ptr - 1) >= 0)
            *(bcd + ptr) += 5;
    }
//    return bcd;
}

unsigned int *BCDToBinary(const char *bcd, unsigned int charSize) {

    char *bcdCopy = charDeepCopy(bcd);
//    unsigned int charSize = len(bcdCopy);
    unsigned int intSize = ceil(log2((double) charSize / 4));
    unsigned int bitSize = ceil(log2(charSize));
    unsigned int *integer = (unsigned int *) malloc(sizeof(unsigned int *) * intSize);

    // region Set all part to zero

    for (int i = 0; i < intSize; i++)
        *(integer + i) = 0;

    // endregion

    while (!BCDZeroCheck(bcdCopy, charSize)) {
        for (int i = (int) bitSize - 1; i >= 0; i--) {
            *(integer + i / 32) |= (*(bcdCopy+charSize-1) %2) << ((bitSize-i)%32);
            divideBCDTo10(bcdCopy, charSize);
        }
    }

    return integer;

}