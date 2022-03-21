#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int my_putchar(char c, int *count)
{
    ++*count;
    return write(1, &c, 1);
}

void print_string(char *s, int *count)
{
    int j = 0;
    while (s[j])
    {
        my_putchar(s[j], count);
        j++;
    }
}

char *utoa(unsigned int num, int base)
{
    char rep[] = "0123456789abcdef";
    char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = rep[num % base];
        num /= base;
    } while (num != 0);

    return (ptr);
}

char my_printf(char *format, ...)
{
    int *count = malloc(sizeof(int));
    char *current;
    int i;
    unsigned int u;
    char *s;
    char buffer[50];
    void *vptr;
    intptr_t *intptr;

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
            print_string(utoa(u, 8), count);
            break;
        case 'u':
            u = va_arg(valist, int);
            print_string(utoa(u, 10), count);
            break;
        case 'x':
            u = va_arg(valist, int);
            print_string(utoa(u, 16), count);
            break;
        case 'p':
            vptr = va_arg(valist, void *);
            intptr_t *intptr = vptr;
            print_string(utoa(intptr, 16), count);
            // itoa(intptr, buffer, 16);
            // print_string(buffer, count);
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
    int a;
    int count;
    int countb;
    count = printf("OG: %d %o %u %x %p %s %c\n", -1234123, -12, -13, -16, &a, "saliduli", 'k');
    printf("%d\n", count);
    countb = my_printf("Mine: %d %o %u %x %p %s %c\n", -1234123, -12, -13, -16, &a, "saliduli", 'k');
    printf("%d\n", countb);
}