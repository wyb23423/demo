#include "calc.h"

#define MAXVAL 100

double val[MAXVAL];
int sp = 0;

void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack overflow, can't push %g\n", f);
    }
}

double pop()
{
    if (sp > 0)
    {
        return val[--sp];
    }

    printf("error: stack empty\n");
    return 0.0;
}

void clear()
{
    sp = 0;
}
