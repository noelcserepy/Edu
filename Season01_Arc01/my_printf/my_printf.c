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

void print_signed(int num, int *count)
{
    char rep[] = "0123456789";
    char buffer[50];
    int i = 0;

    if (num < 0)
    {
        my_putchar('-', count);
        num = num * (-1);
    }

    while (num != 0)
    {
        buffer[i] = rep[num % 10];
        num = num / 10;
        i++;
    }
    for (i = i - 1; i >= 0; i--)
    {
        my_putchar(buffer[i], count);
    }
}

void print_unsigned(unsigned int num, int base, int *count)
{
    char rep[] = "0123456789abcdef";
    char buffer[100];
    int i = 0;

    while (num != 0)
    {
        buffer[i] = rep[num % base];
        num = num / base;
        i++;
    }
    for (i = i - 1; i >= 0; i--)
    {
        my_putchar(buffer[i], count);
    }
}

char *ptoa(void *p, int base)
{
    unsigned long num = (unsigned long)p;
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

    char *s = calloc((strlen(ptr) + 2), sizeof(int));
    strcpy(s, "0x");
    strcat(s, ptr);

    return (s);
}

int my_printf(char *format, ...)
{
    int *count = (int *)malloc(sizeof(int *));
    *count = 0;
    int current = 0;
    int i;
    unsigned int u;
    char *s;
    char buffer[50];
    void *vptr;

    va_list valist;
    va_start(valist, format);

    while (format[current])
    {
        if (format[current] != '%')
        {
            my_putchar(format[current], count);
            current++;
            continue;
        }

        current++;
        switch (format[current])
        {
        case 'd':
            i = va_arg(valist, int);
            print_signed(i, count);
            break;
        case 'o':
            u = va_arg(valist, int);
            print_unsigned(u, 8, count);
            break;
        case 'u':
            u = va_arg(valist, int);
            print_unsigned(u, 10, count);
            break;
        case 'x':
            u = va_arg(valist, int);
            print_unsigned(u, 16, count);
            break;
        case 'p':
            vptr = va_arg(valist, void *);
            s = ptoa(vptr, 16);
            print_string(s, count);
            free(s);
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
        current++;
    }
    va_end(valist);
    return *count;
}

int main(int ac, char **av)
{
    int a;
    int count;

    printf("\nBuiltin printf():\n");
    count = printf("Hi there! %d %o %u %x %p %s %c\n", -1234123, -12, -13, -16, &a, "saliduli", 'o');
    printf("Builtin return value: %d\n\n", count);

    printf("My printf():\n");
    count = my_printf("Hi there! %d %o %u %x %p %s %c\n", -1234123, -12, -13, -16, &a, "saliduli", 'o');
    printf("My return value: %d\n", count);
}