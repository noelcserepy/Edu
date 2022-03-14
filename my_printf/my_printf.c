#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int my_putchar(char c, int *count)
{
    return write(1, &c, 1);
    *count++;
}

// write some code for \ escapes
// return number of chars printed

void print_string(char *s, int *count)
{
    int j = 0;
    while (s[j])
    {
        my_putchar(s[j], count);
        j++;
    }
}

char my_printf(char *format, ...)
{
    int *count = malloc(sizeof(int));
    char *current;
    int i;
    unsigned int u;
    char *s;
    char buffer[50];
    va_list valist;
    va_start(valist, format);

    for (current = format; *current != '\0'; current++)
    {
        while (*current != '%')
        {
            my_putchar(*current, count);
            current++;
        }
        current++;

        switch (*current)
        {
        case 'd':
            i = va_arg(valist, int);
            itoa(i, buffer, 10);
            print_string(buffer, count);
            break;
        case 'o':
            u = va_arg(valist, int);
            itoa(u, buffer, 8);
            print_string(buffer, count);
            break;
        case 'u':
            u = va_arg(valist, unsigned int);
            itoa(u, buffer, 10);
            print_string(buffer, count);
            break;
        case 'x':
            u = va_arg(valist, unsigned int);
            itoa(u, buffer, 16);
            print_string(buffer, count);
            break;
        case 'p':
            i = va_arg(valist, int);
            itoa(i, buffer, 16);
            print_string(buffer, count);
            break;
        case 's':
            s = va_arg(valist, char *);
            print_string(s, count);
            break;
        case 'c':
            i = va_arg(valist, int);
            my_putchar(i, count);
            break;
        }
    }
    va_end(valist);
    return *count;
}

int main(int ac, char **av)
{
    void *a;
    int count;
    count = printf("OG: %d %o %u %x %p %s %c\n", -1234123, 12, -13, 16, a, "saliduli", 'k');
    printf("%d\n", count);
    count = my_printf("Mine: %d %o %u %x %p %s %c\n", -1234123, 12, -13, 16, a, "saliduli", 'k');
    printf("%d\n", count);
}