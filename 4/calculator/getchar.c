#include "calc.h"

#define BUFFSIZE 100

char buff[BUFFSIZE];
int p = 0;

int getch()
{
    return p > 0 ? buff[--p] : getchar();
}

void ungetch(int c)
{
    if (BUFFSIZE <= p)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buff[p++] = c;
    }
}
