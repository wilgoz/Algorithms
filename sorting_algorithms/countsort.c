/*
 * Counting sort demo
 * By: Willy Ghozali
 */

#include <stdio.h>
#include <stdlib.h>

static int get_max(const int list[], const size_t size)
{
    if (size == 1) return list[0];
    if (size == 2) return list[0] > list[1] ? list[0] : list[1];

    size_t divide = size / 2;
    int n = get_max(list, divide);
    int m = get_max(list + divide, size - divide);

    return n > m ? n : m;
}

// Counting sort algorithm O(n + k)
// Returns the sorted array
// Really bad performance with a huge value of k
static int *countsort(const int *list, const size_t size)
{
    int max = get_max(list, size);
    int tot = 0, i = 0;

    int *c      = calloc(max + 1, sizeof *c);
    int *sorted = malloc(size * sizeof *sorted);

    // Count frequencies (index as keys)
    for (i = 0; i < size; i++)
        c[list[i]]++;

    // Prefix sum
    for (i = 0; i <= max; i++)
    {
        tot += c[i];
        c[i] = tot;
    }

    // Slots in the keys to its values/orderings, decrements the order
    // No clue how to do this step without using another buffer
    for (i = 0; i < size; i++)
        sorted[c[list[i]]-- - 1] = list[i];

    free(c);
    return sorted;
}

int main()
{
    const int list[] = {6546, 43242, 54, 222, 222, 456, 32, 1, 45, 11, 432, 44};
    const size_t size = sizeof list / sizeof *list;

    int *sorted = countsort(list, size);
    for (int i = 0; i < size; i++) printf("%d ", sorted[i]);

    free(sorted);
    return 0;
}