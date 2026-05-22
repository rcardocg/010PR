#include <stdio.h>
#include "utils.h"

Result lru(int *pages, int count, int N) {
    int frames[N];
    int last_used[N]; /* last_used[j] = paso en que frames[j] fue usado por ultima vez */
    int size = 0;
    Result r = {0, 0};

    for (int i = 0; i < N; i++) { frames[i] = -1; last_used[i] = -1; }

    printf("\n========== LRU (N=%d) ==========\n", N);
    printf("%-5s %-5s %-8s %-20s %s\n", "step", "ref", "result", "frames", "victim");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int page      = pages[i];
        int victim    = -1;
        int found_idx = -1;

        /* buscar si ya esta en frames */
        for (int j = 0; j < N; j++)
            if (frames[j] == page) { found_idx = j; break; }

        if (found_idx != -1) {
            r.hits++;
            last_used[found_idx] = i; /* actualizar ultimo uso */
            printf("%-5d %-5d %-8s", i+1, page, "HIT");
        } else {
            r.misses++;
            if (size < N) {
                /* hay espacio libre */
                frames[size]    = page;
                last_used[size] = i;
                size++;
            } else {
                /* evictar la pagina con last_used mas antiguo */
                int evict_idx = 0;
                for (int j = 1; j < N; j++) {
                    if (last_used[j] < last_used[evict_idx] ||
                       (last_used[j] == last_used[evict_idx] && frames[j] < frames[evict_idx])) {
                        evict_idx = j;
                    }
                }
                victim               = frames[evict_idx];
                frames[evict_idx]    = page;
                last_used[evict_idx] = i;
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