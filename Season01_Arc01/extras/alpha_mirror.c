#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *alpha_mirror(char *param_1)
{
    char *rev = (char *)malloc(sizeof(param_1));
    int i = 0;

    for (int i = 0; param_1[i] != '\0'; i++)
    {
        if (param_1[i] > 64 && param_1[i] < 91)
        {
            rev[i] = 90 - (param_1[i] - 65);
            continue;
        }
        if (param_1[i] > 96 && param_1[i] < 123)
        {
            rev[i] = 122 - (param_1[i] - 97);
            continue;
        }

        rev[i] = param_1[i];
    }
    return rev;
}

int main()
{
    printf("%s", alpha_mirror("abc zyx"));
    return 0;
}