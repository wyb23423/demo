#include <ctype.h>
#include "calc.h"

int myGetop(char s[])
{
    int c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
    {
        return c;
    }

    int i = 0;
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }

    return NUMBER;
}