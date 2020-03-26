#include <windows.h>
#include <stdio.h>
#include "util.c"

void squeeze(char s1[], const char s2[])
{
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++)
    {
        if (!includes(s1[i], s2))
        {
            s1[j++] = s1[i];
        }
    }

    s1[j] = '\0';
}

int main()
{
    char s[] = "abcdefghijklmnopqrstuvwxyz";
    squeeze(s, "sawedas");

    printf("%s\n", s);

    system("pause");

    return 0;
}