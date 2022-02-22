#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct GameState
{
    char code[10];
    int code_len;
    int attempts;
    char guess[10];
    int well_placed;
    int misplaced;
    int retry;
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

int validate_code(GameState *state, char *code)
{
    if (strlen(code) != 4)
    {
        printf("\nThe code must be EXACTLY 4 characters long.");
        state->retry = 1;
    }
    int has_alpha = 0;
    for (int j = 0; j < strlen(code); j++)
    {
        if (isdigit(code[j]) == 0)
        {
            has_alpha = 1;
        }
    }
    if (has_alpha == 1)
    {
        printf("\nThe code must be numerical.");
        state->retry = 1;
    }
}

int mastermind(GameState *state)
{
    printf("Will you find the secret code?\n---\n");
    // Main game loop
    for (int i = 0; i < state->attempts; i++)
    {
        printf("Round %d\n", i);
        scanf("%s", state->guess);
        validate_code(state, state->guess);

        if (state->retry == 1)
        {
            state->retry = 0;
            i--;
            printf("\nTry again.\n---\n");
            continue;
        }

        compare_codes(state);

        if (state->well_placed == state->code_len)
        {
            printf("Congratz, you did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n---\n", state->well_placed, state->misplaced);
    }
    return 0;
}

void generate_code(GameState *state)
{
    // Generates a random secret code for when user doesn't enter one
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        state->code[i] = (rand() % 8) + 48;
    }
}

void parse_args(int argc, char *argv[], GameState *state)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            state->attempts = atoi(argv[i + 1]);
            if (state->attempts < 1)
            {
                printf("\nThe number of attempts must be a positive integer.");
                state->retry = 1;
            }
        }
        if (strcmp(argv[i], "-c") == 0)
        {
            strcpy(state->code, argv[i + 1]);
            validate_code(state, state->code);
        }
    }
}

int main(int argc, char *argv[])
{
    GameState state;
    state.attempts = 10;
    state.code_len = 4;
    state.retry = 0;

    generate_code(&state);
    parse_args(argc, argv, &state);
    if (state.retry == 1)
    {
        printf("\nTry again.\n---\n");
        return 0;
    }
    mastermind(&state);

    return 0;
}
