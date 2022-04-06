#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    int size;
    char **array;
} string_array;
#endif

string_array *my_split(char *str, char *sep)
{
    char *temp = (char *)malloc(sizeof(str));
    int temp_index = 0;
    int arr_index = 0;
    string_array *arr = malloc(sizeof(struct s_string_array));
    arr->array = malloc(50 * sizeof(char *));

    for (int i = 0; i < strlen(str); ++i)
    {
        if (i == (strlen(str) - 1))
        {
            temp[temp_index] = str[i];
            temp[temp_index + 1] = '\0';
            arr->array[arr_index] = malloc(sizeof(temp));
            strcpy(arr->array[arr_index], temp);
            temp_index = 0;
            arr_index++;
            continue;
        }
        if (str[i] == sep[0])
        {
            temp[temp_index + 1] = '\0';
            arr->array[arr_index] = malloc(sizeof(temp));
            strcpy(arr->array[arr_index], temp);
            temp_index = 0;
            arr_index++;
            continue;
        }
        temp[temp_index] = str[i];
        temp_index++;
    }
    arr->size = arr_index;

    return arr;
}

int main()
{
    string_array *arr = my_split("abc def gh-!", "-");
    return 1;
}