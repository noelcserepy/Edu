#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_define(int num)
{
    if ((num % 2) == 0)
    {
        printf("I have an even number of arguments.\n");
        return;
    }
    printf("I have an odd number of arguments.\n");
}

int main()
{
    my_define(2);
    return 0;
}