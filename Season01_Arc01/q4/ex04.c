#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    int size;
    char **array;
} string_array;
#endif

char *my_join(string_array *param_1, char *param_2)
{
    char *joined = (char *)malloc(100);
    int i = 0;
    for (i = 0; i < param_1->size; i++)
    {
        strcat(joined, param_1->array[i]);
        if (i == param_1->size - 1)
        {
            strcat(joined, param_2);
        }
    }
    printf("%s\n", joined);
    return joined;
}

int main(void)
{
    char sep[] = "hoi";
    struct s_string_array arr;
    arr.size = 3;
    arr.array = (char *[]){"noel", "isch", "lässig"};
    my_join(&arr, sep);
}