#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strip(char *str)
{
    char *ret = (char *)malloc(sizeof(str));
    int index = 0;

    int start = 0;
    while (str[start] == ' ')
    {
        start++;
    }

    int end = strlen(str) - 1;
    while (str[end] == ' ')
    {
        end--;
    }

    for (int i = start; i < end + 1; ++i)
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
    printf("%s", my_strip("       abc        def    hij  "));
    return 1;
}