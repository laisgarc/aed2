#include "grafo_matrizadj.h"


int main() {
    TipoGrafo g1;
    int numVertices;

    inicializaGrafo(&g1, 10);
    imprimeGrafo(&g1);

     insereAresta(&g1, 6, 1, 1);
     insereAresta(&g1, 5, 3, 4);
    // insereAresta(&g1, 0, 3, 2);
    // insereAresta(&g1, 3, 0, 1);
    // insereAresta(&g1, 0, 4, 1);
    // insereAresta(&g1, 4, 0, 1);
    // insereAresta(&g1, 2, 1, 1);
    // insereAresta(&g1, 1, 2, 1);
    // insereAresta(&g1, 2, 3, 1);
    // insereAresta(&g1, 3, 2, 1);
    // insereAresta(&g1, 2, 6, 1);
    // insereAresta(&g1, 6, 2, 1);
    // insereAresta(&g1, 3, 7, 1);
    // insereAresta(&g1, 7, 3, 1);
    // insereAresta(&g1, 1, 5, 1);
    // insereAresta(&g1, 5, 1, 1);
    // insereAresta(&g1, 4, 5, 1);
    // insereAresta(&g1, 5, 4, 1);
    // insereAresta(&g1, 7, 6, 1);
    // insereAresta(&g1, 6, 7, 1);
    // insereAresta(&g1, 4, 7, 1);
    // insereAresta(&g1, 7, 4, 1);
    // insereAresta(&g1, 5, 6, 1);
    // insereAresta(&g1, 6, 5, 1);

     printf("\n");
     imprimeGrafo(&g1);

    TipoApontador adj = primeiroListaAdj(&g1, 1);

    printf("\n %d \n", adj);

    return 0;
}