#include <stdio.h>
#include <stdlib.h>

typedef struct KeyValue
{
    int key;
    int value;
} KV;

int fib(int n, KV *arr, int *arr_len)
{
    printf("arr_len: %d\n", *arr_len);
    for (int i = 0; i < *arr_len; i++)
    {
        if (arr->key == n)
        {
            return arr->value;
        }
    }

    if (n < 0)
        return -1;
    if (n <= 1)
        return n;
    int val = fib(n - 1, arr, arr_len) + fib(n - 2, arr, arr_len);

    KV new;
    new.key = n;
    new.value = val;
    ++*arr_len;
    arr[*arr_len] = new;
    return val;
}

int my_fibonacci(int n)
{
    // KV *cache = malloc((n + 8) * sizeof(KV));
    KV cache[n];
    int arr_len = 0;
    return fib(n, cache, &arr_len);
}

int main()
{
    printf("%d: %d\n", 8, my_fibonacci(8));
    // for (int i = 0; i < 100; i++)
    //     printf("%d: %d\n", i, my_fibonacci(i));
}