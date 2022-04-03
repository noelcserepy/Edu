#include <stdio.h>

int my_iterative_pow(int base, int exponent)
{
    if (exponent < 0)
    {
        return 0;
    }
    int num = 1;
    for (int i = 0; i < exponent; i++)
    {
        num = num * base;
    }
    return num;
}

int main()
{
    printf("%d", my_iterative_pow(2, 4));
}