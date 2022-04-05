#define MAXNUMVERTICES 100
#define AN -1
#define VERTICE_INVALIDO -1

#include <stdbool.h>
#include <stdio.h>

#include "grafo_listaadj.h"

/*
* inicializaGrafo(TipoGrafo* grafo, int nv)
* Cria um grafo com n vertices.
* Aloca espaco para o vetor de apontadores de listas de adjacencias e,
* para cada vertice, inicializa o apontador de sua lista de adjacencia.
* Retorna true se inicializou com sucesso e false caso contrario
* Vertices vao de 1 a nv.
*/
bool inicializaGrafo(TipoGrafo* grafo, int nv) {

    int i;
    
    if(nv <= 0) {
        printf("Erro em inicializaGrafo: número de vertices deve ser positivo.\n");
        return false;
    }

    grafo->numVertices = nv;

    if (!(grafo->listaAdj = (TipoApontador *)calloc(nv + 1, sizeof(TipoApontador)))) {
        printf("Erro: falha na alocação de memória na função inicializaGrafo");
        return false;
    }

    for (i = 0; i < nv; i++) {
        grafo->listaAdj[i] = NULL;
        printf("%d ", grafo->listaAdj[i]);
    }

    grafo->numArestas = 0;

    return true;
}

/*
 * verticeValido(TipoGrafo* grafo, int v):
 * Verifica que o numero do vertice eh valido no grafo.
 */
bool verticeValido(TipoGrafo* grafo, int v) {

    if (v <= 0) {
        printf("ERRO: Número do vertice %d deve ser positivo", v);
        return false;
    }
    if (v > grafo->numVertices) {
        printf("ERRO: Número do vertice (%d) maior que o número total de vértices (%d)", v, grafo->numVertices);
        return false;
    }
    return true;
}

/*
* existeAresta(int v1, int v2, TipoGrafo *grafo):
* Retorna true se existe a aresta (v1, v2) no grafo e false caso contrário
*/
bool existeAresta(TipoGrafo* grafo, int v1, int v2){

    TipoApontador aresta;

    if(!verticeValido(grafo, v1) || !verticeValido(grafo, v2)){
        return false;
    }

    aresta = grafo->listaAdj[v1];

    while(aresta != NULL && aresta->vdest != v2) {
        aresta = aresta -> prox;
    }

    if(aresta != NULL) {
        return true;
    }

    return false;
}

/*
* insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo):
* Insere NÃO ORDENADO a aresta (v1, v2) com peso "peso" no grafo
* Não verifica se a aresta já existe
*/
void insereAresta(TipoGrafo* grafo, TipoPeso peso, int v1, int v2) {

    TipoApontador novaAresta;

    if(!verticeValido(grafo, v1) || !verticeValido(grafo, v2)){
        return;
    }

    if(!(novaAresta = (TipoApontador)calloc(1, sizeof(TipoAresta)))){
        printf("Erro: falha na alocação de memória na função insereAresta\n");
    }

    novaAresta->vdest = v2;
    novaAresta->peso = peso;
    novaAresta->prox = grafo->listaAdj[v1];
    grafo->listaAdj[v1] = novaAresta;
    grafo->numArestas++;

    return;
}

/*
* removeArestaObtendoPeso(TipoGrafo* grafo, TipoPeso peso, int v1, int v2)
* Remove a aresta do grafo
* Se a aresta existia coloca o peso de sua célula em peso e retorna true
* Caso contrário não altera o peso e retorna false
*/
bool removeArestaObtendoPeso(TipoGrafo* grafo, TipoPeso* peso, int v1, int v2) {

    if(!existeAresta(grafo, v1, v2)){
        return false;
    }

    TipoApontador atual, ant;
    atual = grafo->listaAdj[v1];

    while(atual != NULL && atual->vdest != v2) {
        ant = atual;
        atual = atual->prox;
    }

    if(atual != NULL) {
        if (grafo->listaAdj[v1] == atual) grafo->listaAdj[v1] = atual->prox;
        else ant->prox = atual->prox;

        *peso = atual->peso;
        atual->prox = NULL;
        free(atual);
        atual= NULL;
        grafo->numArestas--;

        return true;
    }

    return false;
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
        return false;
    }

    return (grafo->listaAdj[v] == NULL);
}

/*
* primeiroListaAdj(TipoGrafo* grafo, int v)
* Retorna o endereco do primeiro vertice de adjacencia de v
* ou NULL se a lista de adjacencia estiver vazia 
*/
TipoApontador primeiroListaAdj(TipoGrafo* grafo, int v) {

    return (grafo->listaAdj[v]);
}

/*
* proxListaAdj(TipoGrafo* grafo, int v, TipoApontador atual)
* Retorna o proximo vertice adjacente a v, partindo do vertice "atual"
* ou NULL se a lista de adjacencia tiver terminado nem um novo proximo 
*/
TipoApontador proxListaAdj(TipoGrafo* grafo, int v, TipoApontador atual) {

    if(atual == NULL){
        printf("ERRO: Aresta atual e NULL");
        return NULL;
    }

    return(atual->prox);

}

bool FimListaAdj(TipoGrafo* grafo, int v, TipoApontador p) {
    if(p == NULL) return true;

    return false;
}

/*
* imprimeGrafo(TipoGrafo* grafo)
* Imprime os vertices e arestas do grafo no seguinte formato:
* v1: (adj11, peso 11); (adj12, peso12); ...
* v2: (adj21, peso 21); (adj22, peso22); ...
* Assuma que cada vértice e um inteiro de até 2 dígitos
*/

void imprimeGrafo(TipoGrafo* grafo){

    TipoApontador p;
    int i;

    printf("Num de vertices: %d\n", grafo->numVertices);

    for(i = 0; i < grafo->numVertices; i++) {
        printf("%3d: ", i);
        for(p=primeiroListaAdj(i, grafo); !FimListaAdj(grafo, i, p); p=proxListaAdj(grafo, i, p)) {
            printf("(%d, %lf); ", p->vdest, p->peso);
        }
        printf("\n");
    }

}

/* liberaGrafo(TipoGrafo* grafo)
*
*/
void liberaGrafo(TipoGrafo* grafo) {
    int vertice;
    TipoApontador aresta;

    for(vertice = 0; vertice <= grafo->numVertices; vertice++){
        while((aresta = grafo->listaAdj[vertice]) != NULL) {
            grafo->listaAdj[vertice] = aresta->prox;
            aresta->prox = NULL;
            free(aresta);
        }
    }

    grafo->numVertices = 0;
    free(grafo->listaAdj);
    grafo->listaAdj = NULL;
}


/*
  LeGrafo(nomearq, Grafo)
  Le o arquivo nomearq e armazena na estrutura Grafo
  Lay-out: 
    A 1a linha deve conter o número de vertices e o numero de arestas do grafo,
    separados por espaço.
    A 2a linha em diante deve conter a informacao de cada aresta, que consiste
    no indice do vertice de origem, indice do vertice de destino e o peso da 
    aresta, tambem separados por espacos.
    Observações: 
      Os vertices devem ser indexados de 0 a |V|-1
      Os pesos das arestas sao numeros racionais nao negativos.
  
  Exemplo: O arquivo abaixo contem um grafo com 4 vertices (0,1,2,3) e 
  7 arestas. 
  
  4 7
  0 3 6.3
  2 1 5.0
  2 0 9
  1 3 1.7
  0 1 9
  3 1 5.6
  0 2 7.2 
  Codigo de saida:
    1: leitura bem sucedida
    0: erro na leitura do arquivo
*/

bool leGrafo(char* nomearq, TipoGrafo* grafo) {
    FILE* fp;
    int nvertices, narestas;
    int v1, v2;
    TipoPeso peso;
    int i;

    fp = fopen(nomearq, "rt");

    
    printf("Carregando o grafo\n");

    if(fp == NULL){
        printf("O arquivo não existe!\n");
         return false;
    }

    if(fscanf(fp, "%d %d", &nvertices, &narestas) !=2){
        printf("Problemas ao ler nvertices e nArestas");
        return false;
    }

    printf("vertices: %d; arestas: %d;\n", nvertices, narestas);

    inicializaGrafo(grafo, nvertices);

    for(i = 0; i<= narestas; i++){
        if(fscanf(fp, "%d %d %lf", &v1, &v2, &peso) !=3){
            fclose(fp);
            liberaGrafo(grafo);
            return false;
        }

        printf("%d - %d - %d - %d\n", i, v1, v2, peso);
        
        if(v1 < 0 || v1 >= nvertices || v2 < 0 || v2 >= nvertices || peso < 0){
            fclose(fp);
            liberaGrafo(grafo);
            return false;
        }
        insereAresta(grafo, peso, v1, v2);
    }

    printf("Carreguei o grafo\n");

    fclose(fp);


    imprimeGrafo(grafo);

    return true;
}