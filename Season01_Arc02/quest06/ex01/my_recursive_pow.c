#include <stdio.h>

int my_recursive_pow(int base, int exponent)
{
    if (exponent < 0)
    {
        return 0;
    }
    if (exponent)
    {
        return base * my_recursive_pow(base, exponent - 1);
    }
    else
    {
        return 1;
    }
}

int main()
{
    printf("%d", my_recursive_pow(2, 4));
}