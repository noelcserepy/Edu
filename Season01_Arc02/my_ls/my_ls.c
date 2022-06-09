#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "my_ls.h"

// Sorts by mtime
void sort_time(filedata *arr, int total_count)
{
    filedata swap;
    for (int i = 0; i < total_count - 1; i++)
    {
        for (int j = 0; j < total_count - i - 1; j++)
        {
            if (arr[j].mtime < arr[j + 1].mtime)
            {
                swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;
            }
        }
    }
}

void to_lower(char *dest, char *string)
{
    for (int i = 0; i < 255; i++)
    {
        // printf("%d", counter);
        if (string[i] > 64 && string[i] < 91)
        {
            dest[i] = string[i] + 32;
        }
    }
}

// Sorts alphabetically
void sort_alpha(filedata *arr, int total_count)
{
    filedata tmp;
    for (int i = 0; i < total_count - 1; i++)
    {
        for (int j = 0; j < total_count - i - 1; j++)
        {
            // Converting to lowercase in order to sort correctly
            char cmp1[255];
            char cmp2[255];
            to_lower(cmp1, arr[j].name);
            to_lower(cmp2, arr[j + 1].name);
            // printf("%s %s", cmp1, cmp2);

            if (stricmp(arr[j].name, arr[j + 1].name) > 0)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void my_ls(const char *dir, int op_a, int op_t)
{
    DIR *dh = opendir(dir);
    struct dirent *d;
    struct stat filestat;

    // Array for sorting
    filedata *file_array = malloc(sizeof(filedata) * 100);
    int fa_index = 0;

    if (!dh)
    {
        if (errno = ENOENT)
        {
            // If the directory is not found
            perror("Directory doesn't exist");
        }
        else
        {
            // If the directory is not readable then throw error and exit
            perror("Unable to read directory");
        }
        return;
    }

    while ((d = readdir(dh)) != NULL)
    {
        if (!op_a && d->d_name[0] == '.')
        {
            continue;
        }

        filedata fd;

        stat(d->d_name, &filestat);
        if (S_ISDIR(filestat.st_mode))
        {
            strcpy(fd.name, d->d_name);
            strcat(fd.name, "/  "); // Directories with slash
            fd.mtime = filestat.st_mtime;

            file_array[fa_index] = fd;
            fa_index++;
        }
        else
        {
            strcpy(fd.name, d->d_name);
            strcat(fd.name, "  "); // Files without slash
            fd.mtime = filestat.st_mtime;

            file_array[fa_index] = fd;
            fa_index++;
        }
    }

    if (op_t) // Sort if -t flag is used and print vertically
    {
        sort_time(file_array, fa_index);

        for (int i = 0; i < fa_index; i++)
        {
            printf("%3s\n", file_array[i].name);
        }
        return;
    }

    sort_alpha(file_array, fa_index);

    for (int i = 0; i < fa_index; i++)
    {
        printf("%3s", file_array[i].name);
    }

    closedir(dh);
    free(file_array);
}

void parse_args(int argc, char *argv[], char *dirs[], int *dir_count, int *op_a, int *op_t)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-at") == 0)
        {
            *op_a = 1;
            *op_t = 1;
            continue;
        }
        if (strcmp(argv[i], "-ta") == 0)
        {
            *op_a = 1;
            *op_t = 1;
            continue;
        }
        if (strcmp(argv[i], "-a") == 0)
        {
            *op_a = 1;
            continue;
        }
        if (strcmp(argv[i], "-t") == 0)
        {
            *op_t = 1;
            continue;
        }
        if (argv[i][0] != '-')
        {
            dirs[*dir_count] = argv[i];
            ++*dir_count;
        }
    }
}

void sort_dirs_alpha(char *arr[], int total_count)
{
    char *tmp;
    for (int i = 0; i < total_count - 1; i++)
    {
        for (int j = 0; j < total_count - i - 1; j++)
        {
            // Converting to lowercase in order to sort correctly
            char cmp1[255];
            char cmp2[255];
            to_lower(cmp1, arr[j]);
            to_lower(cmp2, arr[j + 1]);
            // printf("%s %s", cmp1, cmp2);

            if (stricmp(arr[j], arr[j + 1]) > 0)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void separate_dirs(char *dirs[], int *dir_count)
{
    char *non_dirs[1000];
    char *tmp_dirs[1000];
    int non_dirs_i = 0;
    int tmp_dirs_i = 0;

    // Separating operands into directory and non-direcotry
    for (int i = 0; i < *dir_count; i++)
    {
        DIR *dh = opendir(dirs[i]);
        if (!dh)
        {
            if (errno = ENOENT)
            {
                // If the directory is not found
                printf("my_ls: cannot access '%s': No such file or directory\n", dirs[i]);
                closedir(dh);
                continue;
            }
            else
            {
                // If the directory is not readable then skip
                printf("my_ls: unable to read directory '%d'\n", dirs[i]);
                closedir(dh);
                continue;
            }

            non_dirs[non_dirs_i] = dirs[i];
            non_dirs_i++;
            closedir(dh);
            continue;
        }
        tmp_dirs[tmp_dirs_i] = dirs[i];
        tmp_dirs_i++;
        closedir(dh);
    }

    for (int i = 0; i < tmp_dirs_i; i++)
    {
        printf("%s", tmp_dirs[i]);
    }

    sort_dirs_alpha(non_dirs, non_dirs_i);
    sort_dirs_alpha(tmp_dirs, tmp_dirs_i);

    // Print out only the non-directory operands
    for (int i = 0; i < non_dirs_i; i++)
    {
        printf("%s  ", non_dirs[i]);
    }

    // Clear original array
    for (int i = 0; i < *dir_count; i++)
    {
        dirs[i] = NULL;
    }

    // Fill original array with only dirs
    for (int i = 0; i < tmp_dirs_i; i++)
    {
        dirs[i] = tmp_dirs[i];
    }

    *dir_count = tmp_dirs_i;

    printf("\n");
}

int main(int argc, char *argv[])
{
    int op_a = 0, op_t = 0;
    char *dirs[1000];
    int dir_count = 0;

    // argc = 2;
    // argv[1] = "sache";
    // argv[2] = "blache";

    parse_args(argc, argv, dirs, &dir_count, &op_a, &op_t);

    if (dir_count < 1)
    {
        dirs[0] = ".";
        dir_count = 1;
    }
    if (dir_count > 1)
    {
        separate_dirs(dirs, &dir_count);
        printf("\n");
        for (int i = 0; i < dir_count; i++)
        {
            printf("%s:\n", dirs[i]);
            my_ls(dirs[i], op_a, op_t);
            printf("\n\n");
        }
        return 0;
    }

    for (int i = 0; i < dir_count; i++)
    {
        my_ls(dirs[i], op_a, op_t);
        printf("\n\n");
    }

    return 0;
}