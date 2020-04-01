#include <stdio.h>
#include <windows.h>

void escape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i] != '\0')
    {
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }

        i++;
    }

    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i] != '\0')
    {
        if (t[i] == '\\')
        {
            switch (t[++i])
            {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            default:
                s[j++] = '\\';
                s[j++] = t[i];
                break;
            }
        }
        else
        {
            s[j++] = t[i];
        }

        i++;
    }

    s[j] = '\0';
}

int main()
{
    char s[62];
    char t[62] = "q278yedhsuad\nfsd\nsgd\tafds\tafcsa\t\t\tfasfa\n\n\nasda15564";

    escape(s, t);
    printf("%s\n\n", s);

    unescape(t, s);
    printf("%s\n", t);

    system("pause");
    return 0;
}