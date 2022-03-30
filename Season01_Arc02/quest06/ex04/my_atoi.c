#include <stdio.h>
#include <string.h>
#include <math.h>

int my_atoi(char *num)
{
    int sign = 1;
    int sum = 0;
    int i = 0;
    if (num[0] == '-')
    {
        sign = -1;
        i++;
    }

    for (; num[i] != '\0'; ++i)
        sum = sum * 10 + num[i] - '0';

    return sign * sum;
}

int main()
{
    printf("%d", my_atoi("-123456789"));
}