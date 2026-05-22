#include <stdio.h>
#include "utils.h"

Result fifo(int *pages, int count, int N) {
    int frames[N];
    int queue[N];   /* cola circular: guarda orden de llegada */
    int front = 0;  /* apunta al mas antiguo                  */
    int size  = 0;  /* cuantos frames ocupados                 */
    Result r  = {0, 0};

    for (int i = 0; i < N; i++) frames[i] = -1;

    printf("\n========== FIFO (N=%d) ==========\n", N);
    printf("%-5s %-5s %-8s %-20s %s\n", "step", "ref", "result", "frames", "victim");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int page   = pages[i];
        int victim = -1;

        if (in_frames(frames, N, page)) {
            r.hits++;
            printf("%-5d %-5d %-8s", i+1, page, "HIT");
        } else {
            r.misses++;
            if (size < N) {
                /* hay espacio libre */
                frames[size] = page;
                queue[size]  = page;
                size++;
            } else {
                /* evictar el mas antiguo */
                victim = queue[front];
                for (int j = 0; j < N; j++)
                    if (frames[j] == victim) { frames[j] = page; break; }
                queue[front] = page;
                front = (front + 1) % N;
            }
            printf("%-5d %-5d %-8s", i+1, page, "MISS");
        }

        print_frames(frames, N);
        if (victim != -1) printf("  evict: %d", victim);
        printf("\n");
    }

    printf("--------------------------------------------------\n");
    return r;
}