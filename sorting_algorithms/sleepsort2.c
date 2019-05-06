/*
 * Sleepsort demo
 * By: Willy Ghozali
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>

typedef struct targs {
    int val;
    int dur;
} targs_t;

static int  _ix = 0;
static int *_sorted;

static void *sort(void *args)
{
    targs_t *targs = args;

    struct timeval tv = {
        .tv_sec  = 0,
        .tv_usec = targs->dur * 1e5
    };

    select(1, NULL, NULL, NULL, &tv);
    _sorted[_ix++] = targs->val;
}

static int get_min(const int list[], const size_t size)
{
    if (size == 1) return list[0];
    if (size == 2) return list[0] < list[1] ? list[0] : list[1];

    size_t divide = size / 2;
    int n = get_min(list, divide);
    int m = get_min(list + divide, size - divide);

    return n < m ? n : m;
}

// Spawns n threads and sleeps each threads according to
// the values of the list in the n-th index
static int *sleepsort(const int *list, const size_t size)
{
    const int min = get_min(list, size);

    targs_t   *targs = malloc(size * sizeof   *targs);
             _sorted = malloc(size * sizeof *_sorted);
    pthread_t *tasks = malloc(size * sizeof   *tasks);

    for (size_t i = 0; i < size; i++)
    {
        targs[i].val = list[i];
        targs[i].dur = list[i] - min;
        pthread_create(&tasks[i], NULL, sort, &targs[i]);
    }

    for (size_t i = 0; i < size; i++) pthread_join(tasks[i], NULL);

    free(tasks);
    free(targs);
    return _sorted;
}

int main()
{
    const int list[] = {6, 5, 7, 13, 17, 5, 7, 13, 17, 13, 14, 12, 8, 9, 11, 6, 20};
    const size_t size = sizeof list / sizeof *list;

    int *sorted = sleepsort(list, size);

    for (int i = 0; i < size; i++) printf("%d ", sorted[i]);
    free(sorted);
    return 0;
}