#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains(const char *str, char c)
{
    for (int i = 0; i < strlen(str); ++i)
        if (str[i] == c)
            return 1;

    return 0;
}

char *inter(char *a, char *b)
{

    char *res = (char *)malloc(sizeof(char) * (strlen(a) + strlen(b)));

    int pushed = 0;

    for (int i = 0; i < strlen(a); ++i)
    {
        if ((!contains(res, a[i])) && contains(b, a[i]))
        {
            res[pushed] = a[i];
            pushed++;
        }
    }

    for (int i = 0; i < strlen(b); ++i)
    {
        if ((!contains(res, b[i])) && contains(a, b[i]))
        {
            res[pushed] = b[i];
            pushed++;
        }
    }

    return res;
}

int main()
{
    char *str1 = "hello";
    char *str2 = "llopadma";

    printf("%s", inter(str1, str2));
    return -1;
}