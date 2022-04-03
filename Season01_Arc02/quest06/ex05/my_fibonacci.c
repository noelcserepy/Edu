#include <stdio.h>

int my_fibonacci(int n)
{
    if (n < 0)
        return -1;
    if (n <= 1)
        return n;
    return my_fibonacci(n - 1) + my_fibonacci(n - 2);
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d: %d\n", i, my_fibonacci(i));
    }
}