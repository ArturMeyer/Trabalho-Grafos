#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include <cstring>
#include "Aresta.h"

using namespace std;

class No
{
private:
    Aresta* primeiraAresta;
    Aresta* ultimaAresta;
    string id;
    int ordemDeInsercao;
    unsigned int grauDeSaida;
    unsigned int grauDeEntrada;
    string Grupo;
    float peso;
    No* proximoNo;
public:
    //CONSTRUTOR
    No(string id);
    //DESTRUTOR
    ~No();
    //SET
    void setProxNo(No* no);
    void setPeso(float val);
    void setPrimeiraAresta(Aresta* Primeira);
    void setUltimaAresta(Aresta* Ultima);
    void setOrdemDeInsercao(int pos);
    void setId(string str);
    void setGrauDeEntrada(unsigned int gE);
    void setGrauDeSaida(unsigned int gS);
    void setGrupo(string G);
    //GET
    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();
    string getId();
    int getGrauDeEntrada();
    int getGrauDeSaida();
    int getOrdemDeInsercao();
    float getPeso();
    No* getProxNo();
    string getGrupo();
    //REMOVER
    void removerArestas(int ord);
    void removeTodasArestas();
};

#endif //NO_H_INCLUDED





