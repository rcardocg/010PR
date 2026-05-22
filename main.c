#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(void) {
    int N;
    int pages[MAX_PAGES];
    int page_count = 0;
    char buf[4096];

    /* --- leer N --- */
    printf("Ingrese el numero de frames (N >= 1): ");
    scanf("%d", &N);
    getchar(); /* consumir el \n que deja scanf */

    if (N < 1) {
        printf("Ingrese un numero valido.\n");
        return 1;
    }

    /* --- leer cadena de referencia --- */
    printf("Ingrese la cadena de referencia (numeros separados por espacio): ");
    if (!fgets(buf, sizeof buf, stdin)) {
        printf("Error leyendo la cadena.\n");
        return 1;
    }

    char *token = strtok(buf, " \t\n");
    while (token != NULL) {
        if (page_count >= MAX_PAGES) {
            printf("Cadena demasiado larga (max %d).\n", MAX_PAGES);
            return 1;
        }
        pages[page_count++] = atoi(token);
        token = strtok(NULL, " \t\n");
    }

    if (page_count == 0) {
        printf("La cadena de referencia no puede estar vacia.\n");
        return 1;
    }

    /* --- correr algoritmos --- */
    Result r_fifo = fifo(pages, page_count, N);
    Result r_min  = min_opt(pages, page_count, N);
    Result r_lru  = lru(pages, page_count, N);

    /* --- resumen final --- */
    print_summary(r_fifo, r_min, r_lru, page_count);

    return 0;
}