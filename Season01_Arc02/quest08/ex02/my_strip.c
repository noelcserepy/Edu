#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strip(char *str)
{
    char *ret = (char *)malloc(strlen(str) * (sizeof(char)));
    int index = 0;

    int start = 0;
    while (str[start] == ' ')
    {
        start++;
    }

    int end = strlen(str);
    while (str[end - 1] == ' ')
    {
        end--;
    }

    for (int i = start; i < end; ++i)
    {
        if (str[i] == ' ')
        {
            while (str[i + 1] == ' ')
            {
                i++;
            }

            ret[index] = ' ';
            index++;
            continue;
        }
        ret[index] = str[i];
        index++;
    }
    ret[index + 1] = '\0';
    return ret;
}

int main()
{
    printf("%s", my_strip("See? It's easy to print the same thing"));
    return 1;
}