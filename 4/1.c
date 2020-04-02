#include <windows.h>
#include <stdio.h>

int strrindex(const char s[], const char t[])
{
    int sLen = strlen(s);
    int tLen = strlen(t);

    if (tLen > sLen || !sLen)
    {
        return -1;
    }

    int j, k;
    for (int i = sLen - tLen; i >= 0; i--)
    {
        for (j = i, k = 0; k < tLen && s[j] == t[k]; k++, j++)
        {
            ;
        }

        if (k >= tLen)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    printf("%d\n", strrindex("aaaaaaaaaaaaaaaaab", "aa"));

    system("pause");
    return 0;
}