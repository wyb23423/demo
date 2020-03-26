#include <stdio.h>
#include <limits.h>
#include <windows.h>

void printRangeByStd()
{
    printf("------ByStd------\n");

    printf("signed   char  min = %d\n", SCHAR_MIN);
    printf("signed   char  max = %d\n", SCHAR_MAX);
    printf("signed   short min = %d\n", SHRT_MIN);
    printf("signed   short max = %d\n", SHRT_MAX);
    printf("signed   int   min = %d\n", INT_MIN);
    printf("signed   int   max = %d\n", INT_MAX);
    printf("signed   long  min = %ld\n", LONG_MIN);
    printf("signed   long  max = %ld\n", LONG_MAX);

    printf("unsigned char  max = %u\n", UCHAR_MAX);
    printf("unsigned short max = %u\n", USHRT_MAX);
    printf("unsigned int   max = %u\n", UINT_MAX);
    printf("unsigned long  max = %u\n", ULONG_MAX);
}

void printRangeByCalc()
{
    unsigned char charMax = (unsigned char)~0;
    unsigned short shortMax = (unsigned short)~0;
    unsigned int intMax = (unsigned int)~0;
    unsigned long longMax = (unsigned long)~0;

    char cMax = (char)(charMax >> 1);
    short sMax = (short)(shortMax >> 1);
    int iMax = (int)(intMax >> 1);
    long lMax = (long)(longMax >> 1);

    printf("------ByCalc------\n");

    printf("signed   char  min = %d\n", -cMax - 1);
    printf("signed   char  max = %d\n", cMax);
    printf("signed   short min = %d\n", -sMax - 1);
    printf("signed   short max = %d\n", sMax);
    printf("signed   int   min = %d\n", -iMax - 1);
    printf("signed   int   max = %d\n", iMax);
    printf("signed   long  min = %ld\n", -lMax - 1);
    printf("signed   long  max = %ld\n", lMax);

    printf("unsigned char  max = %u\n", charMax);
    printf("unsigned short max = %u\n", shortMax);
    printf("unsigned int   max = %u\n", intMax);
    printf("unsigned long  max = %u\n", longMax);
}

int main()
{
    printRangeByStd();
    putchar('\n');
    printRangeByCalc();
    system("pause");
    return 0;
}
