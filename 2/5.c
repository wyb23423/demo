#include <windows.h>
#include <stdio.h>
#include "util.c"

// undefined reference to `includes(char, char const*)' ???
// extern int includes(char c, const char s[]);

int any(const char s1[], const char s2[])
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if (includes(s1[i], s2))
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    printf("%d\n", any("abcdefghijklmnopqrstuvwxyz1234567890", "f"));
    system("pause");

    return 0;
}