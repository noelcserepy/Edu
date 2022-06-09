#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)             \
    do                               \
    {                                \
        size_t __size = (size);      \
        char *__a = (a), *__b = (b); \
        do                           \
        {                            \
            char __tmp = *__a;       \
            *__a++ = *__b;           \
            *__b++ = __tmp;          \
        } while (--__size > 0);      \
    } while (0)
/* Discontinue quicksort algorithm when partition gets below this size.
   This particular magic number was chosen to work best on a Sun 4/260. */
#define MAX_THRESH 4
/* Stack node declarations used to store unfulfilled partition obligations. */
typedef struct
{
    char *lo;
    char *hi;
} stack_node;
/* The next 4 #defines implement a very fast in-line stack abstraction. */
/* The stack needs log (total_elements) entries (we could even subtract
   log(MAX_THRESH)).  Since total_elements has type size_t, we get as
   upper bound for log (total_elements):
   bits per byte (CHAR_BIT) * sizeof(size_t).  */
#define STACK_SIZE (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high) ((void)((top->lo = (low)), (top->hi = (high)), ++top))
#define POP(low, high) ((void)(--top, (low = top->lo), (high = top->hi)))
#define STACK_NOT_EMPTY (stack < top)
/* Order size using quicksort.  This implementation incorporates
   four optimizations discussed in Sedgewick:
   1. Non-recursive, using an explicit stack of pointer that store the
      next array partition to sort.  To save time, this maximum amount
      of space required to store an array of SIZE_MAX is allocated on the
      stack.  Assuming a 32-bit (64 bit) integer for size_t, this needs
      only 32 * sizeof(stack_node) == 256 bytes (for 64 bit: 1024 bytes).
      Pretty cheap, actually.
   2. Chose the pivot element using a median-of-three decision tree.
      This reduces the probability of selecting a bad pivot value and
      eliminates certain extraneous comparisons.
   3. Only quicksorts TOTAL_ELEMS / MAX_THRESH partitions, leaving
      insertion sort to order the MAX_THRESH items within each partition.
      This is a big win, since insertion sort is faster for small, mostly
      sorted array segments.
   4. The larger of the two sub-partitions is always pushed onto the
      stack first, with the algorithm then concentrating on the
      smaller partition.  This *guarantees* no more than log (total_elems)
      stack size is needed (actually O(1) in this case)!  */
void _quicksort(void *const pbase, size_t total_elems, size_t size,
                __compar_d_fn_t cmp, void *arg)
{
    char *base_ptr = (char *)pbase;
    const size_t max_thresh = MAX_THRESH * size;
    if (total_elems == 0)
        /* Avoid lossage with unsigned arithmetic below.  */
        return;
    if (total_elems > MAX_THRESH)
    {
        char *lo = base_ptr;
        char *hi = &lo[size * (total_elems - 1)];
        stack_node stack[STACK_SIZE];
        stack_node *top = stack;
        PUSH(NULL, NULL);
        while (STACK_NOT_EMPTY)
        {
            char *left_ptr;
            char *right_ptr;
            /* Select median value from among LO, MID, and HI. Rearrange
               LO and HI so the three values are sorted. This lowers the
               probability of picking a pathological pivot value and
               skips a comparison for both the LEFT_PTR and RIGHT_PTR in
               the while loops. */
            char *mid = lo + size * ((hi - lo) / size >> 1);
            if ((*cmp)((void *)mid, (void *)lo, arg) < 0)
                SWAP(mid, lo, size);
            if ((*cmp)((void *)hi, (void *)mid, arg) < 0)
                SWAP(mid, hi, size);
            else
                goto jump_over;
            if ((*cmp)((void *)mid, (void *)lo, arg) < 0)
                SWAP(mid, lo, size);
        jump_over:;
            left_ptr = lo + size;
            right_ptr = hi - size;
            /* Here's the famous ``collapse the walls'' section of quicksort.
               Gotta like those tight inner loops!  They are the main reason
               that this algorithm runs much faster than others. */
            do
            {
                while ((*cmp)((void *)left_ptr, (void *)mid, arg) < 0)
                    left_ptr += size;
                while ((*cmp)((void *)mid, (void *)right_ptr, arg) < 0)
                    right_ptr -= size;
                if (left_ptr < right_ptr)
                {
                    SWAP(left_ptr, right_ptr, size);
                    if (mid == left_ptr)
                        mid = right_ptr;
                    else if (mid == right_ptr)
                        mid = left_ptr;
                    left_ptr += size;
                    right_ptr -= size;
                }
                else if (left_ptr == right_ptr)
                {
                    left_ptr += size;
                    right_ptr -= size;
                    break;
                }
            } while (left_ptr <= right_ptr);
            /* Set up pointers for next iteration.  First determine whether
               left and right partitions are below the threshold size.  If so,
               ignore one or both.  Otherwise, push the larger partition's
               bounds on the stack and continue sorting the smaller one. */
            if ((size_t)(right_ptr - lo) <= max_thresh)
            {
                if ((size_t)(hi - left_ptr) <= max_thresh)
                    /* Ignore both small partitions. */
                    POP(lo, hi);
                else
                    /* Ignore small left partition. */
                    lo = left_ptr;
            }
            else if ((size_t)(hi - left_ptr) <= max_thresh)
                /* Ignore small right partition. */
                hi = right_ptr;
            else if ((right_ptr - lo) > (hi - left_ptr))
            {
                /* Push larger left partition indices. */
                PUSH(lo, right_ptr);
                lo = left_ptr;
            }
            else
            {
                /* Push larger right partition indices. */
                PUSH(left_ptr, hi);
                hi = right_ptr;
            }
        }
    }
    /* Once the BASE_PTR array is partially sorted by quicksort the rest
       is completely sorted using insertion sort, since this is efficient
       for partitions below MAX_THRESH size. BASE_PTR points to the beginning
       of the array to sort, and END_PTR points at the very last element in
       the array (*not* one beyond it!). */
#define min(x, y) ((x) < (y) ? (x) : (y))
    {
        char *const end_ptr = &base_ptr[size * (total_elems - 1)];
        char *tmp_ptr = base_ptr;
        char *thresh = min(end_ptr, base_ptr + max_thresh);
        char *run_ptr;
        /* Find smallest element in first threshold and place it at the
           array's beginning.  This is the smallest array element,
           and the operation speeds up insertion sort's inner loop. */
        for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
            if ((*cmp)((void *)run_ptr, (void *)tmp_ptr, arg) < 0)
                tmp_ptr = run_ptr;
        if (tmp_ptr != base_ptr)
            SWAP(tmp_ptr, base_ptr, size);
        /* Insertion sort, running from left-hand-side up to right-hand-side.  */
        run_ptr = base_ptr + size;
        while ((run_ptr += size) <= end_ptr)
        {
            tmp_ptr = run_ptr - size;
            while ((*cmp)((void *)run_ptr, (void *)tmp_ptr, arg) < 0)
                tmp_ptr -= size;
            tmp_ptr += size;
            if (tmp_ptr != run_ptr)
            {
                char *trav;
                trav = run_ptr + size;
                while (--trav >= run_ptr)
                {
                    char c = *trav;
                    char *hi, *lo;
                    for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                        *hi = *lo;
                    *hi = c;
                }
            }
        }
    }
}

{
    int total_count, counter, counter1, swap_var;
    int array[20];
    printf("How many number you want to input?\n");
    scanf("%d", &total_count);
    printf("Please enter %d integers that has to be sorted\n", total_count);
    for (counter = 0; counter < total_count; counter++)
        scanf("%d", &array[counter]);
    for (counter = 0; counter < total_count - 1; counter++)
    {
        for (counter1 = 0; counter1 < total_count - counter - 1; counter1++)
        {
            if (array[counter1] > array[counter1 + 1]) /* For decreasing order use < */
            {
                swap_var = array[counter1];
                array[counter1] = array[counter1 + 1];
                array[counter1 + 1] = swap_var;
            }
        }
    }
    printf("Below is the list of elements sorted in ascending order:\n");
    for (counter = 0; counter < total_count; counter++)
        printf("%d\n", array[counter]);
    return 0;
}

// Sorting algorithm
int compare(const void *a, const void *b)
{
    const filedata *p1 = (filedata *)a;
    const filedata *p2 = (filedata *)b;
    if (p1->mtime < p2->mtime)
        return +1;
    else if (p1->mtime > p2->mtime)
        return -1;
    else
        return 0;
}

void swap(void *v1, void *v2, int size)
{
    // buffer is array of characters which will
    // store element byte by byte
    filedata buffer[size];

    // memcpy will copy the contents from starting
    // address of v1 to length of size in buffer
    // byte by byte.
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

// v is an array of elements to sort.
// size is the number of elements in array
// left and right is start and end of array
//(*comp)(void*, void*) is a pointer to a function
// which accepts two void* as its parameter
void _qsort(void *arr, int size, int left, int right,
            int (*comp)(void *, void *))
{
    filedata *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;

    // casting filedata* to char* so that operations
    // can be done.
    filedata vl = arr + (left * size);
    filedata vr = arr + (mid * size);
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++)
    {

        // vl and vt will have the starting address
        // of the elements which will be passed to
        // comp function.
        vt = (char *)(arr + (i * size));
        if ((*comp)(vl, vt) > 0)
        {
            ++last;
            v3 = (char *)(arr + (last * size));
            swap(vt, v3, size);
        }
    }
    v3 = (char *)(arr + (last * size));
    swap(vl, v3, size);
    _qsort(arr, size, left, last - 1, comp);
    _qsort(arr, size, last + 1, right, comp);
}

void quicksort_method(filedata *arr, int low, int high)
{
    int pivot, value1, value2;
    filedata temp;

    if (low < high)
    {
        pivot = low;
        value1 = low;
        value2 = high;
        while (value1 < value2)
        {
            while (arr[value1].mtime <= arr[pivot].mtime && value1 <= high)
            {
                value1++;
            }
            while (arr[value2].mtime > arr[pivot].mtime && value2 >= low)
            {
                value2--;
            }
            if (value1 < value2)
            {
                temp = arr[value1];
                arr[value1] = arr[value2];
                arr[value2] = temp;
            }
        }
        temp = arr[value2];
        arr[value2] = arr[pivot];
        arr[pivot] = temp;
        quicksort_method(arr, low, value2 - 1);
        quicksort_method(arr, value2 + 1, high);
    }
}