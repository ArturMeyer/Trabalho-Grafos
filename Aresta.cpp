#include "Aresta.h"

Aresta::Aresta(string id){
    idDirecao  = id;
    proximaAresta =  NULL;
    peso = 0;
}

Aresta::~Aresta()
{
    
}

string Aresta::getDirecaoId()
{
    return idDirecao;
}

Aresta* Aresta::getProximaAresta()
{
    return proximaAresta;
}

void Aresta::setProximaAresta(Aresta* prox)
{
    proximaAresta = prox;
}

void Aresta::setPeso(float val)
{
    peso = val;
}

float Aresta::getPeso()
{
    return peso;
}

string Aresta::getGrupo()
{
    return grupo;
}

int Aresta::getOrdemDeInsercao()
{
    return ordemDeInsercao;
}

void Aresta::setOrdemDeInsercao(int pos)
{
    ordemDeInsercao = pos;
}

void Aresta::setIdDirecao(string str)
{
    idDirecao = str;
}

void Aresta::setGrupo(string g)
{
    grupo = g;
}