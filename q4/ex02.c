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

int my_putchar(char c)
{
    return write(1, &c, 1);
}

void my_putstr(char *param_1)
{
    int i = 0;
    while (param_1[i])
    {
        my_putchar(param_1[i]);
        i++;
    }
}

void my_print_words_array(string_array *param_1)
{
    int i = 0;
    while (param_1->array[i])
    {
        my_putstr(param_1->array[i]);
        my_putchar('\n');
        i++;
    }
}

int main(void)
{
    struct s_string_array s;
    s.size = 2;
    s.array = (char *[]){"No", "Problem", "Noel", "You Did Great", NULL};
    my_print_words_array(&s);
}