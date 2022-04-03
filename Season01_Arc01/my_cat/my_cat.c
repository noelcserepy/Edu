#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_cat(int ac, char **av)
{
    if (ac < 2)
    {
        return 0;
    }

    FILE *f_handle;
    char c;

    for (int i = 1; i < ac; i++)
    {
        f_handle = fopen(av[i], "r");
        if (f_handle == NULL)
        {
            printf("Error!");
            exit(1);
        }

        while ((c = getc(f_handle)) != EOF)
        {
            printf("%c", c);
        }
        printf("%c", '\n');
    }
    return 0;
}

int main()
{
    char **arr = (char *[]){"asdf", "file1.txt", "file2.txt"};
    my_cat(3, arr);
    return 0;
}
