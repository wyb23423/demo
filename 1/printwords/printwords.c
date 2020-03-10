#include <stdio.h>

int main()
{
    int c, isWord = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            isWord &&putchar('\n');
            isWord = 0;
        }
        else
        {
            putchar(c);
            isWord = 1;
        }
    }

    return 0;
}