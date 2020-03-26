#include <windows.h>
#include <stdio.h>

int htoi(const char s[])
{
    int i = 0;
    if (s[i] == '0')
    {
        if (s[++i] == 'x' || s[i] == 'X')
        {
            i++;
        }
    }

    int n = 0, inhex = 1;
    int hexdigit;
    for (; inhex; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            hexdigit = s[i] - '0';
        }
        else if (s[i] >= 'a' && s[i] <= 'f')
        {
            hexdigit = s[i] - 'a' + 10;
        }
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            hexdigit = s[i] - 'A' + 10;
        }
        else
        {
            inhex = 0;
        }

        if (inhex)
        {
            n = 16 * n + hexdigit;
        }
    }

    return n;
}

int main()
{
    printf("%d\n", htoi("0x16"));
    system("pause");

    return 0;
}