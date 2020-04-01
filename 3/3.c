#include <stdio.h>
#include <windows.h>

void expand(const char s1[], char s2[])
{
    int i = 0, j = 0;
    int c;
    while ((c = s1[i++]) != '\0')
    {
        if (c != '-' && s1[i] == '-' && s1[i + 1] >= c)
        {
            i++;
            while (c < s1[i])
            {
                s2[j++] = c++;
            }
        }
        else
        {
            s2[j++] = c;
        }
    }

    s2[j] = '\0';
}

int main()
{
    char s[100];
    expand("----------c-a0-9-----a-d-e--g---", s);
    printf("%s\n", s);

    system("pause");
    return 0;
}