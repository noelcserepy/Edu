#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mach(int ac, char **av)
{
    if (ac < 3)
    {
        return 0;
    }

    int x = atoi(av[1]);
    int y = atoi(av[2]);

    char *square = (char *)malloc((x * y) + 1);

    if (x < 1 || y < 1)
    {
        return 0;
    }
    if (x < 2 && y < 2)
    {
        printf("%s", "o");
        return 0;
    }

    char *ends = (char *)malloc(x + 1);
    char *middles = (char *)malloc(x + 1);

    strcat(ends, "o");
    strcat(middles, "|");
    for (int i = 0; i < (x - 2); i++)
    {
        strcat(ends, "-");
        strcat(middles, " ");
    }
    if (x > 1)
    {
        strcat(ends, "o");
        strcat(middles, "|");
    }

    strcat(square, ends);
    strcat(square, "\n");
    for (int i = 0; i < (y - 2); i++)
    {
        strcat(square, middles);
        strcat(square, "\n");
    }
    if (y > 1)
    {
        strcat(square, ends);
        strcat(square, "\n");
    }
    printf("%s", square);
    return 0;
}

int main()
{
    char **arr = (char *[]){"asdf", "4", "4"};
    mach(2, arr);
    return 0;
}
