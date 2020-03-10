#include <stdio.h>
#include <windows.h>

#define MAX_WORDS 20
#define MAX_HEIGHT 20

int getMax(int arr[], int len)
{
    int maxValue = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    return maxValue;
}

int cont(int wl[])
{
    int c, isInWord = 0, i = 0;

    while (i < MAX_WORDS && (c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            isInWord &&i++;
            isInWord = 0;
        }
        else
        {
            wl[i]++;
            isInWord = 1;
        }
    }

    return i;
}

void print()
{
    int wl[MAX_WORDS] = {0};
    int len = cont(wl);
    if (len <= 0)
    {
        return;
    }

    int max = getMax(wl, len);
    int height = max > MAX_HEIGHT ? MAX_HEIGHT : max;
    double rate = height * 1.0 / max;

    for (int i = height; i > 0; i--)
    {
        printf("%d", i);

        for (int j = 0; j < len; j++)
        {
            printf(wl[j] * rate >= i ? " *" : "  ");
        }

        putchar('\n');
    }

    putchar(' ');
    for (int k = 0; k < len; k++)
    {
        printf(" %d", k + 1);
    }

    if (len == MAX_WORDS)
    {
        printf("\n\n");
        print();
    }
}

int main()
{
    print();
    putchar('\n');
    system("pause");

    return 0;
}