#include <stdio.h>
#include <windows.h>

void reverse(char *str)
{
    int len = strlen(str);
    char *p = str + len - 1;
    int itemp = 0;
    while (str < p)
    {
        itemp = *p;
        *p = *str;
        *str = itemp;
        p--;
        str++;
    }
}

int itobReverse(int n, char s[], int b)
{
    int i = 0, sign = n;

    do
    {
        s[i++] = abs(n % b) + '0';
    } while ((n = n / b) != 0);

    sign < 0 && (s[i++] = '-');

    return i;
}

int fill2width(char s[], int w, int len)
{
    if (w < 0)
    {
        return len;
    }

    if (len > w)
    {
        s[w++] = '\0';
        return w;
    }

    while (len < w)
    {
        s[len++] = ' ';
    }

    return len;
}

void itoab(int n, char s[], ...)
{
    va_list ap;
    va_start(ap, s);

    int binary = va_arg(ap, int);
    int w = va_arg(ap, int);

    if (binary < 2 || binary > 16)
    {
        binary = 10;
        w = -1;
    }
    else if (w > 100)
    {
        w = -1;
    }

    int len = 0;
    w != 0 && (len = fill2width(s, w, itobReverse(n, s, binary)));

    s[len] = '\0';
    reverse(s);

    va_end(ap);
}

int main()
{
    char s[100];
    char fmt[] = "%s\n";

    itoab(10000, s);
    printf(fmt, s);

    itoab(10, s, 2);
    printf(fmt, s);

    itoab(10, s, 2, 10);
    printf(fmt, s);

    system("pause");
    return 0;
}