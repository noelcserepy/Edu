#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hidenp(char *str1, char *str2)
{
    int index = 0;
    int len = strlen(str1);

    if (len == 0)
    {
        return 1;
    }

    for (int i = 0; i < strlen(str2); ++i)
    {
        if (index == (len - 1))
        {
            return 1;
        }

        if (str2[i] == str1[index])
        {
            index++;
        }
    }
    return 0;
}

int main()
{
    printf("%d", hidenp("", "brergsrthdfla"));
    return 1;
}