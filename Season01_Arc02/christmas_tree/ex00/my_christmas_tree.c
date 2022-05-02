#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_row(int width, int stars)
{
    int spaces = (width - stars) / 2;

    for (int i = 0; i < spaces; i++)
    {
        putchar(' ');
    }
    for (int i = 0; i < stars; i++)
    {
        putchar('*');
    }
    putchar('\n');
}

void print_base(int width, int base)
{
    int spaces = (width - base) / 2;

    for (int i = 0; i < base; i++)
    {
        for (int i = 0; i < spaces; i++)
        {
            putchar(' ');
        }
        for (int i = 0; i < base; i++)
        {
            putchar('|');
        }
        putchar('\n');
    }
}

int calculate_section_stars(int *stars_array, int *k, int iteration, int start)
{
    int rows = 4 + iteration;
    int end;
    for (int i = 0; i < rows; i++)
    {
        int row_stars = start + (i * 2);
        end = row_stars;
        stars_array[*k] = row_stars;
        ++*k;
    }

    return end;
}

void my_christmas_tree(int sections)
{
    if (sections == 0)
    {
        return;
    }

    int next_start = 1;
    int next_start_decrement = 2;

    int *stars_array = (int *)malloc(sizeof(int) * 100);
    int k = 0;

    for (int i = 0; i < sections; i++)
    {
        if ((i % 2) == 0 && i > 0)
        {
            next_start_decrement += 2;
        }

        int end = calculate_section_stars(stars_array, &k, i, next_start);
        next_start = end - (next_start_decrement);
    }

    int width = stars_array[(k - 1)];

    for (int i = 0; i < (k - 1); i++)
    {
        print_row(width, stars_array[i]);
    }
    print_base(width, sections);
}

int main(int argc, char *argv[])
{
    if (argc > 0)
    {
        int sections = atoi(argv[1]);
        my_christmas_tree(sections);
    }
    else
    {
        printf("You gotta pass the right args man");
    }

    return 0;
}