/*
 * Sleepsort demo
 * By: Willy Ghozali
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int _ix = 0;
static int *_sorted;

// Naive but works
static void *sort(void *val)
{
    sleep(*((int *) val));
    _sorted[_ix++] = *((int *) val);
    return NULL;
}

// Spawns n threads and sleeps each threads according to
// the values of the list in the n-th index
static int *sleepsort(int *list, const size_t size)
{
    pthread_t *tasks = malloc(size * sizeof *tasks);
             _sorted = malloc(size * sizeof *_sorted);

    for (size_t i = 0; i < size; i++) pthread_create(&tasks[i], NULL, sort, &list[i]);
    for (size_t i = 0; i < size; i++) pthread_join(tasks[i], NULL);

    free(tasks);
    return _sorted;
}

int main()
{
    int list[] = {4, 5, 7, 3, 3, 1, 9, 11, 6};
    const size_t size = sizeof list / sizeof *list;

    int *sorted = sleepsort(list, size);

    for (int i = 0; i < size; i++) printf("%d ", sorted[i]);
    free(sorted);
    return 0;
}