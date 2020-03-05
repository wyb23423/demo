#include <stdio.h>

int main()
{
    int c, nl = 0, tl = 0, sl = 0;

    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case ' ':
            sl++;
            break;
        case '\n':
            nl++;
            break;
        case '\t':
            tl++;
            break;
        default:;
        }
    }

    printf("%d %d %d\n", sl, tl, nl);

    return 0;
}
