#include <stdio.h>
#include "utils.h"

/* Regresa el indice futuro donde 'page' aparece en pages[],
   buscando desde 'from' en adelante. Si no aparece regresa
   count (infinito). */
static int next_use(int *pages, int count, int from, int page) {
    for (int i = from; i < count; i++)
        if (pages[i] == page) return i;
    return count;
}

Result min_opt(int *pages, int count, int N) {
    int frames[N];
    int size = 0;
    Result r = {0, 0};

    for (int i = 0; i < N; i++) frames[i] = -1;

    printf("\n========== MIN/OPT (N=%d) ==========\n", N);
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
                frames[size++] = page;
            } else {
                /* evictar la pagina con next-use mas lejano */
                int evict_idx = 0;
                int farthest  = -1;
                for (int j = 0; j < N; j++) {
                    int nu = next_use(pages, count, i+1, frames[j]);
                    if (nu > farthest ||
                       (nu == farthest && frames[j] < frames[evict_idx])) {
                        farthest  = nu;
                        evict_idx = j;
                    }
                }
                victim            = frames[evict_idx];
                frames[evict_idx] = page;
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