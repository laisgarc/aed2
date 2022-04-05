#include <stdbool.h>
#include <stdio.h>

typedef int TipoPeso;

/* 
* Tipo estruturado taresta:
* Vertice destino, peso, ponteiro p/ proxima aresta
*/
typedef struct taresta {
    int vdest;
    TipoPeso peso;
    struct taresta* prox;
} TipoAresta;

typedef TipoAresta* TipoApontador;

/* 
* Tipo estruturado grafo:
* Vetor de listas de adjacencia (cada posicao contem o ponteiro
*               p/ o inicio da lista de adjacencia do vertice)
* Numero de vertices e arestas
*/
typedef struct {
    TipoApontador *listaAdj;
    int numVertices;
    int numArestas;
} TipoGrafo;
