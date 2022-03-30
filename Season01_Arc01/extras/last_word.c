#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *last_word(char *param_1)
{
    int start = 0;
    int end = 0;
    int j = 0;
    char *last = (char *)malloc(20);
    for (int i = 0; i < strlen(param_1); i++)
    {
        if (param_1[i] != ',' && param_1[i] != ' ')
        {
            last[j] = param_1[i];
            j++;
            continue;
        }
        j = 0;
    }
    return last;
}

int main()
{
    printf("%s", last_word("for,ponies"));
    return 0;
}