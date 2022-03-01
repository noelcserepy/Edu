#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int my_putchar(char c)
{
    return write(1, &c, 1);
}

// write some code for \ escapes
// return number of chars printed

char my_printf(char *format, ...)
{
    int arg_count = 0;
    int i = 0;
    while (format[i])
    {
        if (strcmp(format[i], '%') == 0)
        {
            arg_count++;
        }

        i++;
    }
    va_list valist;
    va_start(valist, arg_count);

    for (int i = 0; i < strlen(format); i++)
    {
        if (strcmp(format[i], '%') == 0)
        {
            if (strcmp(format[i + 1], 'doux') == 0) // make this read doux
            {
            }
            if (strcmp(format[i + 1], 'c') == 0)
            {
                char c = va_arg(valist, char);
            }
            if (strcmp(format[i + 1], 's') == 0)
            {
                char *s = va_arg(valist, char *);
            }
            if (strcmp(format[i + 1], 'p') == 0)
            {
                void *p = va_arg(valist, void *);
            }

            arg_count++;
        }
        my_putchar(format[i]);
    }

    va_end(valist);
}

int main(int ac, char **av)
{
    my_printf("hoi");
    printf();
}