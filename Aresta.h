#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED
#include <iostream>
#include <cstring>

using namespace std;

class Aresta
{
private:
    string idDirecao;
    Aresta* proximaAresta;
    float peso;
    int ordemDeInsercao;
    string grupo;
public:
    //CONSTRUTOR
    Aresta(string id);
    Aresta();
    //DESTRUTOR
    ~Aresta();
    //GET
    string getDirecaoId();
    Aresta* getProximaAresta();
    float getPeso();
    int getOrdemDeInsercao();
    string getGrupo();
    //SET
    void setProximaAresta(Aresta* aresta);
    void setPeso(float val);
    void setOrdemDeInsercao(int pos);
    void setIdDirecao(string str);
    void setGrupo(string g);
};

#endif //ARESTA_H_INCLUDED
