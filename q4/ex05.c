#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *my_spaceship(char *param_1)
{
    int x = 0;
    int y = 0;
    char dir[10] = "up";
    char *final_pos = (char *)malloc(100);
    int i = 0;
    int len = strlen(param_1);
    for (i = 0; i < len; i++)
    {
        char inst[] = {param_1[i], '\0'};

        if (strcmp(dir, "up") == 0)
        {
            if (strcmp(inst, "A") == 0)
            {
                y--;
                continue;
            }
            if (strcmp(inst, "R") == 0)
            {
                strcpy(dir, "right");
                continue;
            }
            if (strcmp(inst, "L") == 0)
            {
                strcpy(dir, "left");
                continue;
            }
        }
        if (strcmp(dir, "right") == 0)
        {
            if (strcmp(inst, "A") == 0)
            {
                x++;
                continue;
            }
            if (strcmp(inst, "R") == 0)
            {
                strcpy(dir, "down");
                continue;
            }
            if (strcmp(inst, "L") == 0)
            {
                strcpy(dir, "up");
                continue;
            }
        }
        if (strcmp(dir, "down") == 0)
        {
            if (strcmp(inst, "A") == 0)
            {
                y++;
                continue;
            }
            if (strcmp(inst, "R") == 0)
            {
                strcpy(dir, "left");
                continue;
            }
            if (strcmp(inst, "L") == 0)
            {
                strcpy(dir, "right");
                continue;
            }
        }
        if (strcmp(dir, "left") == 0)
        {
            if (strcmp(inst, "A") == 0)
            {
                x--;
                continue;
            }
            if (strcmp(inst, "R") == 0)
            {
                strcpy(dir, "up");
                continue;
            }
            if (strcmp(inst, "L") == 0)
            {
                strcpy(dir, "down");
                continue;
            }
        }
    }

    snprintf(final_pos, 100, "{x: %d, y: %d, direction: '%s'}", x, y, dir);
    return final_pos;
}

int main()
{
    char str[] = "AAAAAAA";
    my_spaceship(str);
    return 0;
}