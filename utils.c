#include <stdio.h>
#include "utils.h"
 
/* Regresa 1 si 'page' esta en frames[], 0 si no */
int in_frames(int *frames, int N, int page) {
    for (int i = 0; i < N; i++)
        if (frames[i] == page) return 1;
    return 0;
}
 
/* Imprime el contenido actual de los frames */
void print_frames(int *frames, int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        if (frames[i] == -1) printf(" _");
        else                 printf(" %d", frames[i]);
        if (i < N-1) printf(",");
    }
    printf(" ]");
}
 
