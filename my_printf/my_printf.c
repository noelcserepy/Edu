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

void print_arg(char *type_char, va_list va_list)
{
}

char my_printf(char *format, ...)
{
    char *current;
    unsigned int i;
    char *s;
    va_list valist;
    va_start(valist, format);

    for (current = format; *current != '\0'; current++)
    {
        while (*current != '%')
        {
            my_putchar(*current);
            current++;
        }
        current++;

        switch (*current)
        {
        case 'd':
            i = va_arg(valist, int);
            my_putchar(i);
            break;
        case 'o':
            i = va_arg(valist, int);
            my_putchar(i);
            break;
        case 's':
            s = va_arg(valist, char *);
            int j = 0;
            while (j < strlen(s))
            {
                my_putchar(s[j]);
                j++;
            }
            break;
        case 'x':
            i = va_arg(valist, int);
            my_putchar(i);
            break;
        case 'c':
            i = va_arg(valist, int);
            my_putchar(i);
            break;
        }
    }
    va_end(valist);
}

int main(int ac, char **av)
{
    my_printf("hoi %s %p %d", "gaggi", "1234123", "3");
}