#ifndef UTILS_H
#define UTILS_H

#define MAX_PAGES 256

typedef struct {
    int hits;
    int misses;
} Result;

/* utils.c */
int  in_frames(int *frames, int N, int page);
void print_frames(int *frames, int N);

/* fifo.c */
Result fifo(int *pages, int count, int N);

/* min.c */
Result min_opt(int *pages, int count, int N);

/* lru.c */
Result lru(int *pages, int count, int N);

/* summary.c */
void print_summary(Result r_fifo, Result r_min, Result r_lru, int count);

#endif