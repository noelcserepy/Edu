#include <stdio.h>

int my_iterative_factorial(int num)
{
    if (num < 1)
    {
        return 0;
    }
    int fact = num;
    for (int i = num - 1; i > 1; i--)
    {
        fact = fact * i;
    }
    return fact;
}

int main()
{
    printf("%d", my_iterative_factorial(4));
}