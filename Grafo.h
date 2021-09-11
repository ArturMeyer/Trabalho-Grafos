#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <cstring>
using namespace std;
#include "No.h"

typedef struct {
    No* id;
    Aresta* idDirecao;
} aresta;

typedef struct {
    float media;
    int numSolucoes;
} Media;

typedef struct {
    float p;
    string grupo;
} item;

class Grafo
{
private:
    int ordem;
    int numeroArestas;
    bool direcionado;
    bool pesoArestas;
    bool pesoNos;
    No* primeiroNo;
    No* ultimoNo;
    int adicionados;
    int numGrupos;
    int pesoArvore;

    //AUX
    void auxProfundidade(string v, int visitado[], ofstream *arquivo, int *t);
    void auxFechoTransitivoDireto(string id, int visitado[], ofstream *arquivo);
    bool auxFechoTransitivoIndireto(string id, int visitado[], No* escolhido, bool *possui, ofstream *arquivo);


public:
    //CONSTRUTOR
    Grafo();
    Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoNos);
    //DESTRUTOR
    ~Grafo();
    //GET
    int getOrdem();
    int getNumeroDeArestas();
    bool getDirecionado();
    bool getPesoArestas();
    bool getPesoNos();
    No* getPrimeiroNo();
    No* getUltimoNo();
    No* getNo(string id);
    int getPesoArvore();
    //SET
    void setOrdem(int ord);
    void setNumGrupos(int num);
    void setPesoArvore(int peso);
    //INSERE
    void insereNo(string id);
    void insereAresta(string id, string idDirecao, float peso);
    //REMOVE
    void removeNo(string id);
    //IMPRIME
    void imprime();
    //GERA ARQUIVO
    void geraArquivoDot(string arquivoSaida, string nome);
    //PROCURA
    bool procuraNo(string Id);
    //BUSCA EM PROFUNDIDADE
    void profundidade(string v, string arquivo, int *t);
    //ARVORES
    Grafo* arvoreMinimaKruskal(string subConjuntoVertices[], int tam, string arquivo);
    Grafo* arvoreMinimaPrim(string subConjuntoVertices[], int tam, string arquivo);
    //ORDENAR
    void ordenaNosPorPeso(aresta sub[], int tam); 
    void QuickSort(aresta sub[], int p, int q);
    int particionamento(aresta sub[], int p, int q);
    void troca(aresta *a, aresta *b);
    //CAMINHO MÍNIMO
    void moore_Dijkstra(string noInicial, string noFinal);
    void floyd(string noInicial, string noFinal);
    //ODENAÇÃO TOPOLÓGICA
    void ordencaoTopologica();
    //COPIA
    Grafo* copiaGrafo();
    //FECHO TRANSITIVO
    void fechoTransitivoDireto(string id, string arquivo);
    void fechoTransitivoIndireto(string id, string arquivo);
    //GULOSO
    float arvoreMinimaGeneralizadaGuloso();
    //GULOSO RANDOMIZADO
    float arvoreMinimaGeneralizadaGulosoRandomizado(float alfa, int numIter);
    //GULOSO RANDOMIZADO REATIVO
    float arvoreMinimaGeneralizadaGulosoRandomizadoReativo(float alfa[], int numIter, int bloco, int m);
    void inicializaVetores(float P[], Media A[], int m);
    void atualizaProbabilidades(float P[], Media A[], Grafo* melhorSolucao, int m);
    void atualizaMedias(Media A[], Grafo* solucao, float alfa, int m, float alfas[]);
    int escolheAlfa(float P[], int m);

};

#endif