#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void my_ngram(int argc, char **argv)
{
    int *counts = calloc(127, sizeof(int));
    int counts_len = 127;
    char *str = malloc(sizeof(argv[1]));

    // Looping through all input strings
    for (int k = 1; k < argc; k++)
    {
        str = argv[k];
        // Counting characters
        for (int i = 1; i < 127; i++)
        {
            int j = 0;
            while (str[j] != '\0')
            {
                if (j == '\"')
                {
                    continue;
                }
                if (str[j] == i)
                {
                    counts[i]++;
                }
                j++;
            }
        }
    }

    // Printing results
    for (int i = 0; i < counts_len; i++)
    {
        if (counts[i] == 0)
        {
            continue;
        }
        printf("%c: %d\n", i, counts[i]);
    }
}

int main(int argc, char *argv[])
{
    argv = (char *[]){
        "/path/to/out", "\"gaggi\""};
    argc = 2;
    my_ngram(argc, argv);
    return 0;
}