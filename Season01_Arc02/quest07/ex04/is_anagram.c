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

int is_anagram(char *a, char *b)
{
    int *countsA = (int *)calloc(127, sizeof(int));
    int *countsB = (int *)calloc(127, sizeof(int));

    for (int i = 0; i < strlen(a); ++i)
    {
        countsA[a[i]]++;
    }
    for (int i = 0; i < strlen(b); ++i)
    {
        countsB[b[i]]++;
    }

    for (int i = 0; i < 127; i++)
    {
        if (countsA[i] != countsB[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char *a = "bfut";
    char *b = "tubf";
    printf("%d", is_anagram(a, b));
    return -1;
}