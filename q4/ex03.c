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

#ifndef STRUCT_INTEGER_ARRAY
#define STRUCT_INTEGER_ARRAY
typedef struct s_integer_array
{
    int size;
    int *array;
} integer_array;
#endif

void printcount(integer_array *count);

integer_array *my_count_on_it(string_array *param_1)
{
    struct s_integer_array *count = malloc(sizeof(integer_array));
    count->size = param_1->size;
    count->array = (int *)malloc(sizeof(int) * (param_1->size));
    int len;
    int i = 0;
    for (int i = 0; i < param_1->size; i++)
    {
        len = strlen(param_1->array[i]);
        count->array[i] = len;
    }
    return count;
}

int main(void)
{
    struct s_string_array s;
    s.size = 4;
    s.array = (char *[]){"No", "Problem", "Noel", "You Did Great"};
    struct s_integer_array *count = malloc(sizeof(integer_array));
    count = my_count_on_it(&s);
    printf("%d", count->array[0]);
}