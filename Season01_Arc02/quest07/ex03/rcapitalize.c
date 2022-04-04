#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isCapital(char c)
{
    if (c > 64 && c < 91)
        return 1;

    if (c > 96 && c < 123)
        return -1;

    return 0;
}

char *rcapitalize(char *a)
{

    char *res = (char *)malloc(strlen(a));
    int pushed = 0;

    for (int i = 0; i < strlen(a); ++i)
    {
        if (a[i + 1] == ' ' || (i + 1) >= strlen(a))
        {
            if (isCapital(a[i]) == -1)
            {
                res[pushed] = a[i] - 32;
                pushed++;
                continue;
            }
            res[pushed] = a[i];
            pushed++;
            continue;
        }

        if (isCapital(a[i]) == 1)
        {
            res[pushed] = a[i] + 32;
            pushed++;
            continue;
        }
        res[pushed] = a[i];
        pushed++;
    }

    res[pushed] = '\0';
    return res;
}

int main()
{
    char *str1 = "But... This iS not THAT COMPLEX";
    printf("%s", rcapitalize(str1));
    return -1;
}