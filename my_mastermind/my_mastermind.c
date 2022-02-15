#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct GameState
{
    char code[10];
    int code_len;
    int attempts;
    char guess[10];
    int well_placed;
    int misplaced;
} GameState;

void compare_codes(GameState *state)
{
    int well = 0;
    int mis = 0;

    for (int i = 0; i < state->code_len; i++)
    {
        for (int j = 0; j < state->code_len; j++)
        {
            if (state->guess[j] == state->code[i])
                mis++;
        }
        if (state->guess[i] == state->code[i])
        {
            well++;
            mis--;
        }
    }

    state->well_placed = well;
    state->misplaced = mis;
}

int mastermind(GameState *state)
{

    printf("Will you find the secret code?\n---\n");

    for (int i = 0; i < state->attempts; i++)
    {
        printf("Round %d\n", i);
        scanf("%s", state->guess);

        compare_codes(state);

        if (state->well_placed == state->code_len)
        {
            printf("Congratz, you did it!");
            return 0;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n---\n", state->well_placed, state->misplaced);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    GameState state;
    state.attempts = 10;
    state.code_len = 4;

    // Generate a random secret code
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        state.code[i] = (rand() % 8) + 48;
    }

    // Parse argv
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            state.attempts = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-c") == 0)
        {
            strcpy(state.code, argv[i + 1]);
        }
    }

    mastermind(&state);

    return 0;
}
