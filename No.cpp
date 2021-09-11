#include <iostream>
#include "No.h"

No::No(string Id)
{
    id = Id;
    primeiraAresta = ultimaAresta  = NULL;
    proximoNo = NULL;
    grauDeEntrada = grauDeSaida = peso = 0;
}

No::~No()
{

}

void No::removerArestas(int ord)
{
    Aresta* a = primeiraAresta;
    Aresta* ant;

    while (a != NULL)
    {
        if(a->getOrdemDeInsercao() == ord)
        {
            if(a == primeiraAresta)
            {
                primeiraAresta = a->getProximaAresta();
                ant = a;
                delete a;
                if(primeiraAresta == NULL)
                    ultimaAresta == NULL;
            }else if(a == ultimaAresta)
            {
                ultimaAresta = ant;
                ant->setProximaAresta(NULL);
                delete a;
                if(ultimaAresta == NULL)
                    primeiraAresta == NULL;
            }else
            {
                ant->setProximaAresta(a->getProximaAresta());
                ant = a;
                delete a;
            }
            grauDeSaida--;
        }

        if(a->getOrdemDeInsercao() > ord)
            a->setOrdemDeInsercao(a->getOrdemDeInsercao() -1);
        ant = a;
        a = a->getProximaAresta();
    }
    
}

void No::removeTodasArestas()
{
    Aresta* a = primeiraAresta;
    while(a!=NULL)
    {
        Aresta* t = a->getProximaAresta();
        delete a;
        a = t;
    }
    
}

void No::setProxNo(No* p)
{
    proximoNo  = p;
}

void No::setPeso(float val)
{
    peso = val;
}

Aresta* No::getPrimeiraAresta()
{
    return primeiraAresta;
}

Aresta* No::getUltimaAresta()
{
    return ultimaAresta;
}

string No::getId()
{
    return id;
}

int No::getGrauDeEntrada()
{
    return grauDeEntrada;
}

int No::getGrauDeSaida()
{
    return grauDeSaida;
}

int No::getOrdemDeInsercao()
{
    return ordemDeInsercao;
}


float No::getPeso()
{
    return peso;
}

No* No::getProxNo()
{
    return proximoNo;
}

void No::setPrimeiraAresta(Aresta* primeira)
{
    primeiraAresta = primeira;
}

void No::setUltimaAresta(Aresta* ultima)
{
    ultimaAresta = ultima;
}

void No::setOrdemDeInsercao(int pos)
{
    ordemDeInsercao = pos;
}

void No::setId(string str)
{
    id = str;
}

void No::setGrauDeEntrada(unsigned int gE)
{
    grauDeEntrada = gE;
}

void No::setGrauDeSaida(unsigned int gS)
{
    grauDeSaida = gS;
}

/////

string No::getGrupo()
{
    return Grupo;
}

void No::setGrupo(string G)
{
    Grupo = G;
}