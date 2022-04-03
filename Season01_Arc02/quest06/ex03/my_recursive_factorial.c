#include <stdio.h>

int my_recursive_factorial(int num)
{
    if (num < 0)
    {
        return 0;
    }
    if (num > 1)
    {
        return num * my_recursive_factorial(num - 1);
    }
}

int main()
{
    printf("%d", my_recursive_factorial(4));
}