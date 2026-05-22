#include <stdio.h>
#include "utils.h"

void print_summary(Result r_fifo, Result r_min, Result r_lru, int count) {
    printf("\n========== RESUMEN COMPARATIVO ==========\n");
    printf("%-10s %-8s %-8s %-10s\n", "Algoritmo", "Hits", "Misses", "Hit Rate");
    printf("-----------------------------------------\n");
    printf("%-10s %-8d %-8d %.2f%%\n", "FIFO", r_fifo.hits, r_fifo.misses, 100.0 * r_fifo.hits / count);
    printf("%-10s %-8d %-8d %.2f%%\n", "MIN/OPT",  r_min.hits,  r_min.misses,  100.0 * r_min.hits  / count);
    printf("%-10s %-8d %-8d %.2f%%\n", "LRU",  r_lru.hits,  r_lru.misses,  100.0 * r_lru.hits  / count);
    printf("-----------------------------------------\n");
}