#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **my_split(char *str, char *sep)
{
    int previous_cut = 0;
    char *push = (char *)malloc(sizeof(str));
    int push_index = 0;
    char **ret = malloc(50 * sizeof(char *));
    int ret_index = 0;

    for (int i = 0; i < strlen(str); ++i)
    {
        if ((str[i] == sep[0]) || i == (strlen(str) - 1))
        {
            push[push_index + 1] = '\0';
            ret[ret_index] = malloc(sizeof(push));
            strcpy(ret[ret_index], push);
            push_index = 0;
            ret_index++;
            continue;
        }
        push[push_index] = str[i];
        push_index++;
    }
    return ret;
}

int main()
{
    char **arr = my_split("abc def hij", " ");

    for (int i = 0; i < 3; i++)
    {
        printf("%s ", arr[i]);
    }
    return 1;
}