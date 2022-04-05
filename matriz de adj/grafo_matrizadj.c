#define MAXNUMVERTICES 100
#define AN -1
#define VERTICE_INVALIDO -1

#include <stdbool.h>
#include <stdio.h>

#include "grafo_matrizadj.h"

/*
* inicializaGrafo(TipoGrafo* grafo, int nv)
* Inicializa um grafo com nv vértices
* Preenche as células com AN (representando ausência de aresta)
* Vértices vão de 1 a nv.
*/
bool inicializaGrafo(TipoGrafo* grafo, int nv) {

    int i, j;
    if (nv > MAXNUMVERTICES) {
        fprintf(stderr, "Numero de vértices maior que o permitido\n");
        return false;
    }
    if(nv <= 0) {
        fprintf(stderr, "Numero de vértices deve ser positivo\n");
        return false;
    }
    grafo->numVertices = nv;
    for(i = 0; i <= grafo->numVertices; i++){
        for(j = 0; j <= grafo->numVertices; j++){
            grafo->mat[i][j] = AN;
        }
    }
    return true;
}

/*
 * verticeValido(TipoGrafo* grafo, int v):
 * Verifica que o numero do vertice eh valido no grafo.
 */
bool verticeValido(TipoGrafo* grafo, int v) {

    if (v <= 0) {
        fprintf(stderr, "ERRO: Número do vertice %d deve ser positivo", v);
        return false;
    }
    if (v > grafo->numVertices) {
        fprintf(stderr, "ERRO: Número do vertice (%d) maior que o número total de vértices (%d)", v, grafo->numVertices);
        return false;
    }
    return true;
}

/*
* existeAresta(int v1, int v2, TipoGrafo *grafo):
* Retorna true se existe a aresta (v1, v2) no grafo e false caso contrário
*/
bool existeAresta(TipoGrafo* grafo, int v1, int v2){

    if(!verticeValido(grafo, v1) || !verticeValido(grafo, v2)){
        return false;
    }

    if(grafo->mat[v1][v2] == AN){
        return false;
    }

    return true;
}

/*
* insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo):
* Insere a aresta (v1, v2) com peso "peso" no grafo
*/
bool insereAresta(TipoGrafo* grafo, TipoPeso peso, int v1, int v2) {

    if(existeAresta(grafo, v1, v2)){
        return false;
    }

    if(!verticeValido(grafo, v1) || !verticeValido(grafo, v2)){
        return false;
    }

    grafo->mat[v1][v2] = peso;
    grafo->numArestas++;

    return true;
}

/*
* removeAresta(TipoGrafo* grafo, int v1, int v2)
* Remove a aresta do grafo colocando AN na sua célula (indicando ausência de aresta)
* Se a aresta existia retorna true, senão false
*/
bool removeAresta(TipoGrafo* grafo, int v1, int v2) {

    if(!existeAresta(grafo, v1, v2)){
        return false;
    }

    grafo->mat[v1][v2] = AN;
    grafo->numArestas--;

    return true;
}

/*
* removeArestaObtendoPeso(TipoGrafo* grafo, TipoPeso peso, int v1, int v2)
* Remove a aresta do grafo colocando AN na sua célula (indicando ausência de aresta)
* Se a aresta existia coloca o peso de sua célula em peso e retorna true
* Caso contrário não altera o peso e retorna false
*/
bool removeArestaObtendoPeso(TipoGrafo* grafo, TipoPeso* peso, int v1, int v2) {

    if(!existeAresta(grafo, v1, v2)){
        return false;
    }

    *peso = grafo->mat[v1][v2];
    grafo->mat[v1][v2] = AN;
    grafo->numArestas--;

    return true;
}

/*
* obtemPesoAresta(TipoGrafo* grafo, int v1, int v2) 
* Retorna o peso da aresta no grafo caso ela exista
* e AN caso não exista
*/
TipoPeso obtemPesoAresta(TipoGrafo* grafo, int v1, int v2) {

    if(!existeAresta(grafo, v1, v2)){
        return AN;
    }

    return grafo->mat[v1][v2];

}

/*
* obtemNrVertices(TipoGrafo* grafo)
* Retorna o numero de vertices do grafo
*/
int obtemNrVertices(TipoGrafo* grafo) {
    return grafo->numVertices;
}

/*
* obtemNrArestas(TipoGrafo* grafo)
* Retorna o numero de arestas do grafo
*/
int obtemNrArestas(TipoGrafo* grafo) {
    return grafo->numArestas;
}

/*
* listaAdjVazia(TipoGrafo* grafo, int v)
* Retorna true se a lista de adjacencia do vertice v é vazia,
* e false caso contrário 
*/
bool listaAdjVazia(TipoGrafo* grafo, int v) {

    if(!verticeValido(grafo, v)){
        return true;
    }

    for(int i = 1; i <= grafo->numVertices; i++){
        if(grafo->mat[v][i] != AN){
            return false;
        }
    }
    return true;
}

/*
* primeiroListaAdj(TipoGrafo* grafo, int v)
* Retorna o primeiro vertice de adjacencia de v
* ou VERTICE_INVALIDO se a lista de adjacencia estiver vazia 
*/
TipoApontador primeiroListaAdj(TipoGrafo* grafo, int v) {

    if(listaAdjVazia(grafo, v)){
        return VERTICE_INVALIDO;
    }

    return grafo->mat[v][1];
}

/*
* proxListaAdj(TipoGrafo* grafo, int v, TipoApontador atual)
* Trata-se de um iterador sobre a lista de adjacência do vertice v
* Retorna o proximo vertice adjacente a v, partindo do vertice "atual"
* ou VERTICE_INVALIDO se a lista de adjacencia tiver terminado nem um novo proximo 
*/
TipoApontador proxListaAdj(TipoGrafo* grafo, int v, TipoApontador atual) {

    if(listaAdjVazia(grafo, v)){
        return VERTICE_INVALIDO;
    }

    for(int i = atual +1; i <= grafo->numVertices; i++){
        if(grafo->mat[v][i] != AN){
            return i;
        }
    }

    return VERTICE_INVALIDO;

}

/*
* imprimeGrafo(TipoGrafo* grafo)
* Imprime a matriz de adjacencia do grafo
* Assuma que cada vértice e cada peso de aresta são inteiros de até 2 dígitos
*/

void imprimeGrafo(TipoGrafo* grafo){

    for(int i = 1; i <= grafo->numVertices; i++){
        for(int j = 1; j <= grafo->numVertices; j++){
            printf("%d ", grafo->mat[i][j]);
        }
        printf("\n");
    }

}
