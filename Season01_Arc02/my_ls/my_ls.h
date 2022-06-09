#ifndef MY_LS_H
#define MY_LS_H

// Struct used to hold file info for sorting
typedef struct Filedata
{
    char name[255]; // Maximum filename length in linux
    int mtime;
} filedata;

int compare(const void *a, const void *b);
void sort_time(filedata *arr, int total_count);

#endif