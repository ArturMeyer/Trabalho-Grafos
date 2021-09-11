#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <array>
#include "Grafo.h"
#include "Aresta.h"
#include "No.h"

using namespace std;

//CONSTRUTOR
Grafo::Grafo()
{
    ordem = 0;
    direcionado = 0;
    pesoArestas = 1;
    pesoNos = 0;
    primeiroNo = ultimoNo = NULL;
    adicionados = 0;
    pesoArvore = 0;
}

//CONSTRUTOR
Grafo::Grafo(int ord, bool direc, bool pesoA, bool pesoN)
{   
    ordem = ord;
    direcionado = direc;
    pesoArestas = pesoA;
    pesoNos = pesoN;
    primeiroNo = ultimoNo = NULL;
    adicionados = 0;
    pesoArvore = 0;
}

//DESTRUTOR
Grafo::~Grafo()
{
    No* p = primeiroNo;
    while(p != NULL)
    {
        p->removeTodasArestas();
        No* t = p->getProxNo();
        delete p;
        p = t;
    }
}

//RETORNA ORDEM DO GRAFO
int Grafo::getOrdem()
{
    return ordem;
}

//RETORNA NÚMERO DE ARESTAS
int Grafo::getNumeroDeArestas()
{
    return numeroArestas;
}

//RETORNA SE O GRAFO É DIRECIONADO
bool Grafo::getDirecionado()
{
    return direcionado;
}

//RETORNA PESO DAS ARESTAS
bool Grafo::getPesoArestas()
{
    return pesoArestas;
}

//RETORNA PESO DOS NÓS
bool Grafo::getPesoNos()
{
    return pesoNos;
}

//RETORNA PRIMEIRO NÓ
No* Grafo::getPrimeiroNo()
{
    return primeiroNo;
}

//RETORNA ULTIMO NÓ
No* Grafo::getUltimoNo()
{
    return ultimoNo;
}

//RETORNA O PESO DA ÁRVORE
int Grafo::getPesoArvore()
{
    return pesoArvore;
}

//MUDA A ORDEM DO GRAFO
void Grafo::setOrdem(int ord)
{
    ordem = ord;
}

//MUDA O NÚMERO DE GRUPOS DO GRAFO
void Grafo::setNumGrupos(int num)
{
    numGrupos = num;
}

//MUDA O PESO DA ÁRVORE
void Grafo::setPesoArvore(int peso)
{
    pesoArvore = peso;
}

//RETORNA NÓ A PARTIR DE UM ID
No* Grafo::getNo(string Id)
{
    //Recebe primeiro nó
    No* n = primeiroNo;

    //Verifica se o grafo está vazio
    if(primeiroNo == NULL)
        return NULL;

    //Percorre o grafo até encontrar um nó com id desejado
    while(n->getId() != Id)
    {
        n = n->getProxNo();
        if(n == NULL)
        {
            break;
        }
    }

    //Se não existir retorna NULL
    if(n == NULL)
    {
        return NULL;
    }

    //Se existir retorna o nó
    return n;
}

//INSERE UM NÓ NA LISTA
void Grafo::insereNo(string id)
{
    //Gera um novo nó com o id
    No* novo = new No(id);
    
    //Se o grafo está vazio esse nó é o primeiro 
    if (primeiroNo == NULL)
    {
        primeiroNo = novo;
    }
    //Se não está vazio vira o último
    else{
        ultimoNo->setProxNo(novo);
    }
    ultimoNo = novo;
    novo->setProxNo(NULL); 
    novo->setOrdemDeInsercao(adicionados);

    adicionados++;
    
}

//INSERE UMA NOVA ARESTA NO GRAFO
void Grafo::insereAresta(string Id, string idDirect, float peso)
{
    //Recupera o nó com Id
    No* noUm = getNo(Id);
    No* noDois = getNo(idDirect);

    //Verifica se os nós não existem
    if(noUm == NULL)
    {
        insereNo(Id);
    }
    if(noDois == NULL)
    {
        insereNo(idDirect);
    }
    
    //Recupera os nós caso não existiam antes 
    if(noUm == NULL)
    {
        noUm = getNo(Id);
    }
    if(noDois == NULL)
    {
        noDois = getNo(idDirect);
    }

    //Se o grafo for direcionado aumenta o grau de entrada e de saída dos nós
    if(direcionado)
    {
        int GS = noUm->getGrauDeSaida() + 1;
        noUm->setGrauDeSaida(GS);
        int GE = noDois->getGrauDeEntrada() + 1;
        noDois->setGrauDeEntrada(GE);
    }

    //Cria nova aresta com sua direção
    Aresta* nova = new Aresta(idDirect);

    nova->setGrupo(noDois->getGrupo());

    //Insere nova aresta 
    //Se não existe aresta essa é a primeira 
    if(noUm->getPrimeiraAresta() == NULL)
    {
        noUm->setPrimeiraAresta(nova);
    }
    //Se existe essa é a última
    else
    {
        noUm->getUltimaAresta()->setProximaAresta(nova);
    }
    nova->setPeso(peso);
    nova->setOrdemDeInsercao(noDois->getOrdemDeInsercao());
    noUm->setUltimaAresta(nova);
    nova->setProximaAresta(NULL);

    /*Se o grafo não é direcionado existe uma aresta de noUm para noDois
        e de noDois para noUM
    */
    if(direcionado == 0)
    {
        //Cria nova aresta com sua direção
        nova = new Aresta(Id);
        nova->setGrupo(noUm->getGrupo());
        //Insere nova aresta 
        if(noDois->getPrimeiraAresta() == NULL)
        {
            noDois->setPrimeiraAresta(nova);
        }else
        {
            noDois->getUltimaAresta()->setProximaAresta(nova);
        }
        nova->setPeso(peso);
        nova->setOrdemDeInsercao(noUm->getOrdemDeInsercao());
        noDois->setUltimaAresta(nova);
        nova->setProximaAresta(NULL);

    }

    //Aumenta o número de arestas
    numeroArestas++;
    
}

//IMPRIME O GRAFO
void Grafo::imprime()
{
    //Recupera o primeiro nó
    No* p = primeiroNo;

    Aresta* a;
    cout << "Ordem: " << ordem << endl;
    cout << "Grupos: " << numGrupos << endl;
    cout << "Peso: " << pesoArvore << endl;

    //Percorre o grafo 
    while (p != NULL)
    {
        //Recupera a primeira aresta do nó
        a = p->getPrimeiraAresta();
        cout << p->getId() << "-" << p->getGrupo() << " " << p->getOrdemDeInsercao() << "\t";
        while(a != NULL)
        {
            cout << a->getDirecaoId() << " ";
            a = a->getProximaAresta();
        }
        cout << endl;
        p = p->getProxNo();
    }
    cout << endl;
}

//PROCURA UM NÓ A PARTIR DO ID
bool Grafo::procuraNo(string str)
{
    //Recupera o primero nó
    No* p = primeiroNo;

    //Percorre os nós
    while (p != NULL)
    {
        //Se o id do nó é igual a do passado retorta true
        if(str == p->getId())
            return true;
        p = p->getProxNo();
    }
    //Se não encontrar retorna false
    return false;
}

//GERA UM ARQUIVO DOT A PARTIR DO GRAFO
void Grafo::geraArquivoDot(string arquivoSaida, string nome)
{
    //Abre o arquivo de saída
    ofstream saida;
    saida.open(arquivoSaida);

    No* p = primeiroNo;
    Aresta* a;

    bool adicionado[ordem];

    //Imprime de acordo com a direção do grafo
    if(direcionado == 0)
         saida << "graph " << nome << "{" << endl;
    else
         saida << "digraph " << nome << "{" << endl;
   
    //Percorre  o grafo
    while (p != NULL)
    {
        a = p->getPrimeiraAresta();

        //Deixa o nó marcado em sua posição como adicionado no arquivo
        adicionado[p->getOrdemDeInsercao()] = true;

        //Percorre as arestas
        while(a != NULL)
        {
            //Se a aresta ainda não foi adicionada
            if(adicionado[a->getOrdemDeInsercao()] == false || direcionado == 1)
            {
                //Verifica se o grafo é direcionado
                if(direcionado == 0 )
                    saida << p->getId() << " -- " <<  a->getDirecaoId();
                else
                    saida << p->getId() << " -> " <<  a->getDirecaoId();

                //Verifica se possui peso nas arestas
                if(pesoArestas == true)
                {
                    saida << " [label=" << a->getPeso() << "]";
                }

                a = a->getProximaAresta();
                saida << endl;
            }
            //Se a aresta já foi adicionada passa para próxima aresta
            else
                a = a->getProximaAresta();
        }
        p = p->getProxNo();
    }
    saida << "}" << endl;
}

//CHAMA FUNÇÃO AUXILIAR PARA CAMINHAR NO GRAFO EM PROFUNDIDADE
void Grafo::profundidade(string v, string arquivo, int *t)
{
    ofstream saida;

    saida.open(arquivo);

    if(direcionado == 0)
         saida << "graph " << "G" << "{" << endl;
    else
         saida << "digraph " << "G" << "{" << endl;

    //Vetor para verificar se o nó já está na solução
    int visitado[ordem];
    //Marcar todos nós como ainda não visitados
    for(int i = 0; i < ordem; i++) visitado[i] = 0;
    int i = 0;
    auxProfundidade(v, visitado, &saida, t);

    saida << "}" << endl;
}

//FUNÇÃO RECURSIVA PARA CAMINHAR EM PROFUNDIDADE
void Grafo::auxProfundidade(string v, int visitado[], ofstream *arquivo, int *t)
{
    //Retorna o nó do v correspondente
    No* n = getNo(v);
    //Se não existe o programa para
    if(n == NULL)
    {
        cout << "Nao existe o no" << v << endl;
        exit(3);
    }
    (*t)++;

    //Recupera a primeira aresta do nó
    Aresta* a = n->getPrimeiraAresta();

    //Marca o nó como visitado
    visitado[n->getOrdemDeInsercao()] = 1;

    //Percorre o grafo
    while(a != NULL)
    {
        //Se o nó ainda não foi visitado
        if(visitado[a->getOrdemDeInsercao()] == 0)
        {
            cout << v << " -- " <<  a->getDirecaoId() << endl;
            *arquivo << v << " -- " << a->getDirecaoId() << endl;
            //Chama função recursivamente para o nó não visitdo
            auxProfundidade(a->getDirecaoId(), visitado, arquivo, t); 

        }
        //Se é uma aresta que não foi utilizada
        else if(visitado[a->getOrdemDeInsercao()] == -1 )
        {
            cout << v << " -- " <<  a->getDirecaoId() << " [style=dotted]" << endl;
            *arquivo << v << " -- " <<  a->getDirecaoId() << " [style=dotted]" << endl;
        }

        a = a->getProximaAresta();
    }
    //Marcar nó que suas arestas serão pontilhadas
    visitado[n->getOrdemDeInsercao()] = -1;
}

//ENCONTRAR CAMINHO MÍNIMO A PARTIR DO ALGORÍTMO DE DIJKSTRA
void Grafo::moore_Dijkstra(string noInicial, string noFinal)
{
    string pi[ordem];
    int d[ordem];
    No* vertices[ordem];

    No* p = primeiroNo;
    
    //Recuperandos nós final e inicial  
    No* inicial = getNo(noInicial);
    No* final = getNo(noFinal);

    //Preenchendo vetores 
    for(int i = 0; i < ordem; i++)
    {
        vertices[i] = p;
        d[i] = 1400000;
        pi[i] = "-1";
        p = p->getProxNo();
    }

    //Colocando valor 0 na posição inicial
    d[inicial->getOrdemDeInsercao()] = 0;

    int itens = ordem;
    int cont = 1;

    //Começando loop até a lista acabar
    while(itens != 0)
    {
        int min = 0;

        //Encontra o valor inicial válido
        while (vertices[min] == NULL)
        {
            min++;
        }

        //Encontra a menor distância
        for(int i = 0; i < ordem; i++)
        {
            if(d[min] > d[i] && vertices[i] != NULL)
            {
                min = i;
            }
        }

        itens--;

        //Encontra a primeira aresta do vertice mínimo
        Aresta* A = vertices[min]->getPrimeiraAresta();

        //Percorre os adjacentes do vértice mínimo 
        while(A != NULL)
        {
            for(int k = 0; k < ordem; k++){
                if(k == A->getOrdemDeInsercao() && d[k] > A->getPeso() + d[min] )
                {
                    d[k] =  A->getPeso() + d[min];
                    if(d[final->getOrdemDeInsercao()] != 1400000 && pi[cont-1] != vertices[min]->getId())
                    {
                        pi[cont] = vertices[min]->getId();
                        cont++;
                    }
                }
            }
            A = A->getProximaAresta(); 
        }
        
        if(vertices[min]->getId() == noFinal)
        {
            pi[cont] = vertices[min]->getId();
            cont++;
            break;
        }

        vertices[min] = NULL;

    }

    if(d[final->getOrdemDeInsercao()] == 1400000)
    {
        cout << "Nao existe caminho" << endl;
        return;
    }else
    {
        cout << "Resultado: " << d[final->getOrdemDeInsercao()] << " ";
    }

    
}

//ENCONTRAR CAMINHO MÍNIMO A PARTIR DO ALGORÍTMO DE FLOYD
void Grafo::floyd(string noInicial, string noFinal)
{
    int i = 0;
    int j = 0;
    item A[ordem][ordem];

    //Recupera nó inicial e final
    No* inicial = getNo(noInicial);
    No* final = getNo(noFinal);

    No* p = primeiroNo;
    Aresta* a;

    //Inicia matriz
    for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            A[i][j].p = 99999;
        }
    }

    //Percorre  a grafo e a matriz e inicia ela com os pesos 
    for(i = 0; i < ordem; i++)
    {
        a = p->getPrimeiraAresta();
        
        while(a != NULL)
        {
            for(j = 0; j < ordem; j++)
            {
                if(i == j)
                {
                    A[i][j].p = 0;
                    A[i][j].grupo = p->getGrupo();
                }
                else if( a->getOrdemDeInsercao() == j)
                {
                    A[i][j].p = a->getPeso();
                    A[i][j].grupo = p->getGrupo();
                }
                
            }
            a = a->getProximaAresta();
        }
        p = p->getProxNo();
    }

    //Atualiza matriz até encontra A[i][j] mínimos
    for(int k = 0; k < ordem; k++)
    {
        for(i = 0; i < ordem; i++)
        {
            for(j = 0; j < ordem; j++)
            {
                if(A[i][k].p+A[k][j].p < A[i][j].p)
                    A[i][j].p = A[i][k].p+A[k][j].p;
            }
        }
    }
    int sol[numGrupos];
    for(int i = 0; i < numGrupos-1; i++)
    {
        sol[i] = -1;
    }
    int min = 99999;
    int total = 0;
    for(int k = 1; k < numGrupos; k++)
    {
        int min = 99999;
        for(i = 0; i < ordem; i++)
        {
            for(j = 0; j < ordem; j++)
            {
                if(A[i][j].p < min && A[i][j].grupo == to_string(k) && A[i][j].p != 0)
                {
                    min = A[i][j].p;
                    cout << "I: " << i << " - " << "J: " << j << " " << A[i][j].grupo << endl;
                }
            }
        }
        cout << min << endl;
        sol[k] = min;
        total += min;
    }

    cout << total << endl;

    if(A[inicial->getOrdemDeInsercao()][final->getOrdemDeInsercao()].p == 99999)
    {
        cout << "Nao existe caminho" << endl;
        return;
    }else
    {
        cout << "Resultado: " << A[inicial->getOrdemDeInsercao()][final->getOrdemDeInsercao()].p << " ";
    }
}

//REMOVE NÓ DO GRAFO
void Grafo::removeNo(string id)
{
    No* D = getNo(id);
    No* p = primeiroNo;
    No* ant = NULL;

    //Percorre o grafo
    while(p != NULL)
    {
        //Se é o nó que será removido
        if(p->getId() == id)
        {
            Aresta* a = p->getPrimeiraAresta();
            //Se é o primeiro nó
            if(p == primeiroNo)
            {
                //Próximo nó vai ser o primeiro
                primeiroNo = p->getProxNo();
                //Apaga o as arestas que esse nó possui
                //E atualiza o grau de entrada dos nós adjacentes
                while(a!=NULL)
                {
                    Aresta* t = a->getProximaAresta();
                    No* adj =  getNo(a->getDirecaoId());
                    adj->setGrauDeEntrada(adj->getGrauDeEntrada() - 1);
                    delete a;
                    a = t;
                }
                //Deleta o nó
                delete p;
                //Se o grafo ficar vazio
                if(primeiroNo == NULL)
                    ultimoNo == NULL;
            }
            //Se for o último nó 
            else if(p == ultimoNo)
            {
                //O último nó será o nó anterior ao removido
                ultimoNo = ant;
                ant->setProxNo(NULL);
                while(a!=NULL)
                {
                    Aresta* t = a->getProximaAresta();
                    No* adj =  getNo(a->getDirecaoId());
                    adj->setGrauDeEntrada(adj->getGrauDeEntrada() - 1);
                    delete a;
                    a = t;
                }
                delete p;
                if(ultimoNo == NULL)
                    primeiroNo == NULL;
            }
            //Se está no meio
            else
            {
                //O anterior aponta para o próximo nó
                ant->setProxNo(p->getProxNo());
                while(a!=NULL)
                {
                    Aresta* t = a->getProximaAresta();
                    No* adj =  getNo(a->getDirecaoId());
                    adj->setGrauDeEntrada(adj->getGrauDeEntrada() - 1);
                    delete a;
                    a = t;
                }
                delete p;
            }
            
            //Armazenar o nó anterior
            if(ant != NULL)
                p = ant;
            else
                p = primeiroNo;

        }
        //Se não é o nó a ser removido
        else
        {
            //Se o nó tem ordem de inserção menor do que o removido
            //Diminui sua ordem de inserção
            if(p->getOrdemDeInsercao() > D->getOrdemDeInsercao())
                p->setOrdemDeInsercao(p->getOrdemDeInsercao() - 1); 
            //Remove todas aretas com o nó removido
            p->removerArestas(D->getOrdemDeInsercao());
            //Armazena anterior
            ant = p;
            p = p->getProxNo();
        }
    }
    //Diminui ordem e adicionados
    ordem--;
    adicionados--;
}

//GERA UMA ÁRVORE MÍNIMA A PARTIR DO ALGORÍTMO DE KRUSKAL
Grafo* Grafo::arvoreMinimaKruskal(string subConjuntoVertices[], int tam, string arquivo)
{
    No* sub[tam];
    aresta arestas[numeroArestas];
    int subArvores[ordem];
    Grafo* solucao = new Grafo(tam, 0, 1, 0);
    Grafo* G = new Grafo(tam, 0, 1, 0);
    int cont = 0, contador = 0;

    //ADICIONA OS NÒS E GERA AS SUBARVORES
    for(int i = 0; i < tam; i++)
    {
        sub[i] = getNo(subConjuntoVertices[i]);
        subArvores[sub[i]->getOrdemDeInsercao()] = sub[i]->getOrdemDeInsercao();
    }

    //FAZ UM VETOR COM AS ARESTAS 
    for(int i = 0; i < tam; i++)
    {
        Aresta* a = sub[i]->getPrimeiraAresta();
        while(a != NULL)
        {
            for(int j = i+1; j < tam; j++)
            {
                if(a->getDirecaoId() == sub[j]->getId())
                {
                    arestas[cont].id = sub[i];
                    arestas[cont].idDirecao = a;
                    cont++;
                    G->insereAresta(sub[i]->getId(), a->getDirecaoId(), a->getPeso());
                }
            }

            a = a->getProximaAresta();
        }
    }

    //ORDENA AS ARESTAS
    QuickSort(arestas, 0, cont-1);

    int itensNaLista = cont + 1;
    int peso = 0;

    while(contador < tam-1 && itensNaLista != 0)
    {
        aresta A = arestas[0];
        //Remove a aresta 
        for(int i = 0; i < cont-1; i++)
        {
            arestas[i] = arestas[i+1];
        }
        //Diminui o número de itens
        itensNaLista--;
        //Se os nós não estão na mesma subárvore
        if((subArvores[A.idDirecao->getOrdemDeInsercao()] != subArvores[A.id->getOrdemDeInsercao()]))
        {
            int maior; 

            //Insere a aresta na solção
            solucao->insereAresta(A.id->getId(), A.idDirecao->getDirecaoId(), A.idDirecao->getPeso());

            peso += A.idDirecao->getPeso();
            
            //Junta as subárvores dos nós na menor e atualiza o vetor subArvores[]
            if(subArvores[A.idDirecao->getOrdemDeInsercao()] < subArvores[A.id->getOrdemDeInsercao()])
            {
                maior = subArvores[A.id->getOrdemDeInsercao()];
                subArvores[A.id->getOrdemDeInsercao()] = subArvores[A.idDirecao->getOrdemDeInsercao()];
            }else
            {
                maior = subArvores[A.idDirecao->getOrdemDeInsercao()];
                subArvores[A.idDirecao->getOrdemDeInsercao()] = subArvores[A.id->getOrdemDeInsercao()];
            }
            contador++;
            for(int i = 0; i < ordem; i++)
            {
                if(subArvores[i] == maior)
                {
                    subArvores[i] = subArvores[A.idDirecao->getOrdemDeInsercao()];
                }
            }
        }
    }
    solucao->setPesoArvore(peso);
    return solucao;
}

//RETORNA O PESO DA ARESTA ENTRE DOIS NÓS
float c(string str, string u, aresta arestas[], int tam)
{
    //Percorre o vetor de arestas e enconta o peso entre esses dois nós
    for(int i = 0; i < tam; i++)
    {
        if(arestas[i].id->getId() == str && arestas[i].idDirecao->getDirecaoId() == u)
        {
            return arestas[i].idDirecao->getPeso();
        }
        else if(arestas[i].id->getId() == u && arestas[i].idDirecao->getDirecaoId() == str)
        {
            return arestas[i].idDirecao->getPeso();
        }
    }
    //Se os nós são iguais 
    if(str == u)
    {
        return 0;
    }
    //Se não exxiste a aresta
    return 9999999999999;
}

//GERA UMA ÁRVORE MÍNIMA A PARTIR DO ALGORÍTMO DE PRIM
Grafo* Grafo::arvoreMinimaPrim(string subConjuntoVertices[], int tam, string arquivo)
{
    No* sub[tam];
    aresta arestas[numeroArestas];
    Grafo* solucao = new Grafo(tam, 0, 1, 0);
    string prox[tam];
    float aux[tam];
    int cont = 0, contador = 0;

    //ADICIONA OS NÒS E GERA AS SUBARVORES
    for(int i = 0; i < tam; i++)
    {
        sub[i] = getNo(subConjuntoVertices[i]);
    }

    //FAZ UM VETOR COM AS ARESTAS 
    for(int i = 0; i < tam; i++)
    {
        Aresta* a = sub[i]->getPrimeiraAresta();
        while(a != NULL)
        {

            for(int j = i+1; j < tam; j++)
            {
                if(a->getDirecaoId() == sub[j]->getId())
                {
                    arestas[cont].id = sub[i];
                    arestas[cont].idDirecao = a;
                    cont++;
                }
            }

            a = a->getProximaAresta();
        }
    }

    if(cont == 0)
    {
        cout << "Nao existe arestas entre os vertices" << endl;
        return NULL;
    }

    //ORDENA AS ARESTAS
    QuickSort(arestas, 0, cont-1);

    //Insere a aresta de menor peso na solução
    solucao->insereAresta(arestas[0].id->getId(), arestas[0].idDirecao->getDirecaoId(), arestas[0].idDirecao->getPeso());
    
    //Inicia os vetores com o custo de cada nó para o nó de menor peso
    for(int i = 0; i < tam; i++)
    {
        float UateI = c(sub[i]->getId() , arestas[0].id->getId(), arestas, cont);
        float VateI = c(sub[i]->getId() , arestas[0].idDirecao->getDirecaoId(), arestas, cont);
        if(UateI > VateI)
        {
            prox[i] = arestas[0].idDirecao->getDirecaoId();
            aux[i] = VateI;
        }
        else
        {
            prox[i] = arestas[0].id->getId();
            aux[i] = UateI;
        }
        if(sub[i]->getId() == arestas[0].id->getId())
        {
            prox[i] = "0";
        }
        if(sub[i]->getId() == arestas[0].idDirecao->getDirecaoId())
        {
            prox[i] = "0";
        }
    }

    //Pega a aresta de peso mínimo e adiciona no grafo
    while(contador < tam-2)
    {
        
        float min = 10000000000000;
        int index;
        for(int i = 0; i < tam; i++)
        {
            if(min > aux[i]  && aux[i] != 0 && prox[i] != "0")
            {
                min = aux[i];
                index = i;
            }
        }
        solucao->insereAresta(prox[index], sub[index]->getId(), aux[index]);
        prox[index] = "0";

        //Atualiza vetores
        for(int i = 0; i < tam; i++)
        {
            float UateI = c(sub[i]->getId(), prox[i], arestas, cont);
            float VateI = c(sub[i]->getId(),sub[index]->getId(), arestas, cont);
            if(prox[i] != "0" && UateI > VateI)
            {
                prox[i] = sub[index]->getId();
                aux[i] = VateI;
            }
        }
        contador++;
    }
    
    solucao->geraArquivoDot(arquivo, "G");
    return solucao;
} 

//CHAMA FUNÇÃO RECURSIVA PARA ENCONTRAR O FECHO TRANSITIVO DIRETO DE UM NÓ
void Grafo::fechoTransitivoDireto(string id, string arquivo)
{
    ofstream saida;

    saida.open(arquivo);

    if(direcionado == 0)
         saida << "graph " << "G" << "{" << endl;
    else
         saida << "digraph " << "G" << "{" << endl;
    
    //Verifica se o grafo é direcionado
    if(!direcionado)
    {
        cout << "Grafo nao direcionado" << endl;
        return;
    }
    //Recupera o nó
    No* n = getNo(id);
    //Se o grau de saida é igual a 0 não possui fecho transitivo direto
    if(n->getGrauDeSaida() == 0)
    {
        cout << "Nao possui" << endl;
        return;
    }
    int visitado[ordem];
    for(int i = 0; i < ordem; i++) visitado[i] = 0;
    int i = 0;
    //Chama função recursiva
    auxFechoTransitivoDireto(id, visitado, &saida);

    saida << "}" << endl;
}

//FUNÇÃO RECURSIVA PARA ENCONTRAR O FECHO TRANSITIVO DIRETO DE UM NÓ
void Grafo::auxFechoTransitivoDireto(string id, int visitado[], ofstream *arquivo)
{
    //Recupera nó
    No* n = getNo(id);
    //Se o nó não existe
    if(n == NULL)
    {
        cout << "Nao existe o no" << id << endl;
        exit(3);
    }
    Aresta* a = n->getPrimeiraAresta();
    //Marca o nó como visitado
    visitado[n->getOrdemDeInsercao()] = 1;

    //Percorre as arestas
    while(a != NULL)
    {
        if(visitado[a->getOrdemDeInsercao()] == 0)
        {
            cout << a->getDirecaoId() << " ";
            *arquivo << id << " -> " <<  a->getDirecaoId() << endl;
            //Chama função recursivamente
            auxFechoTransitivoDireto(a->getDirecaoId(), visitado, arquivo); 
        }

        a = a->getProximaAresta();
    }
}

//CHAMA FUNÇÃO RECURSIVA PARA ENCONTRAR O FECHO TRANSITIVO INDIRETO DE UM NÓ
void Grafo::fechoTransitivoIndireto(string id, string arquivo)
{
    ofstream saida;
    
    saida.open(arquivo);

    if(direcionado == 0)
         saida << "graph " << "G" << "{" << endl;
    else
         saida << "digraph " << "G" << "{" << endl;
    
    //Verifica se o grafo é direcionado
    if(!direcionado)
    {
        cout << "Grafo nao direcionado" << endl;
        return;
    }
    int visitado[ordem];
    bool possui = false;
    //Marca os nós como não visitados
    for(int i = 0; i < ordem; i++) visitado[i] = 0;
    No* escolhido = getNo(id);

    //Se o nó não possui grau de entrada não possui fecho transitivo indireto
    if(escolhido->getGrauDeEntrada() == 0)
    {
        cout << "Nao possui" << endl;
        return;
    }

    No* p = primeiroNo;
    Aresta* a;

    //Percorre os vértices e verifica se em seu fecho transitivo direto possui o vétice escolhido
    while(p != NULL)
    {
        //Chama a função recursiva
        auxFechoTransitivoIndireto(p->getId(), visitado, escolhido, &possui, &saida);
        //Verifica se possui o vértice escolhido e se não é ele mesmo
        if(possui == true && p->getId() != escolhido->getId())
        {
            cout << p->getId() << " ";
            a = p->getPrimeiraAresta();
            while(a != NULL)
            {   
                if(p->getId() != escolhido->getId())
                    saida << p->getId() << " -> " << a->getDirecaoId() << endl;
                if(a->getDirecaoId() == escolhido->getId())
                {
                    break;
                }
                a = a->getProximaAresta();
            }
        }
        p = p->getProxNo();
        //Reseta os valores
        possui = false;
        for(int i = 0; i < ordem; i++) visitado[i] = 0;
    }
    cout << endl;

    saida << "}" << endl;
}

//FUNÇÃO RECURSIVA PARA ENCONTRAR O FECHO TRANSITIVO INDIRETO DE UM NÓ
bool Grafo::auxFechoTransitivoIndireto(string id, int visitado[], No* escolhido, bool *possui, ofstream *arquivo)
{
    No* n = getNo(id);
    //Verifica se existe
    if(n == NULL)
    {
        cout << "Nao existe o no" << id << endl;
        exit(3);
    }
    Aresta* a = n->getPrimeiraAresta();
    //Marca o nó como visitado
    visitado[n->getOrdemDeInsercao()] = 1;
    //Verifivca se é o nó escolhido
    if(n->getId() == escolhido->getId())
    {
        *possui = true;
        return possui;
    }
    while(a != NULL)
    {
        if(visitado[a->getOrdemDeInsercao()] == 0)
        {
            auxFechoTransitivoIndireto(a->getDirecaoId(), visitado, escolhido, possui, arquivo); 
        }

        a = a->getProximaAresta();
    }
    return possui;
}

//RETORNA UMA CÓPIA DO GRAFO
Grafo* Grafo::copiaGrafo()
{
    Grafo* G = new Grafo(ordem, direcionado, pesoArestas, pesoNos);
    No* p = primeiroNo;
    Aresta* a;

    //Percorre o grafo inserindo as arestas no novo grafo
    while (p != NULL)
    {
        a = p->getPrimeiraAresta();
        while(a != NULL)
        {
            G->insereAresta(p->getId(), a->getDirecaoId(), a->getPeso());
            a = a->getProximaAresta();
        }
        p = p->getProxNo();
    }
    return G;
}

//RETORNA A ORDENAÇÃO TOPOLÓGICA DO GRAFO
void Grafo::ordencaoTopologica()
{
    string S[ordem];
    //Copia o grafo
    Grafo *G = copiaGrafo();
    No* p = G->primeiroNo;
    Aresta* a; 

    //Percorre o grafo procurando nós com grau de entrada 0 
    //Se achar remove o nó
    for (int i = 0; i < ordem; i++)
    {
        p = G->primeiroNo;
        while (p != NULL)
        {
            if(p->getGrauDeEntrada() == 0)
            {
                S[i] = p->getId();
                G->removeNo(p->getId());
                break;
            }
            p = p->getProxNo();
        }
    }

    if(S[0].length() == 0 )
    {
        cout << "Existe Loop" << endl;
    }else
    {
        for (int i = 0; i < ordem; i++)
        {
            cout << S[i] << " ";
        }
        cout << endl;
    }
    
    

}

//ALGORITMO GULOSO PARA O PROLEMA DA ÁRVORE GERADORA MÍNIMA GERERALIZADA
//RETORNA O PESO DA ÁRVORE GERADA
float Grafo::arvoreMinimaGeneralizadaGuloso()
{
    No* sub[ordem];
    int pi[numGrupos+1];
    aresta* arestas = new aresta[numeroArestas];
    Grafo* T = new Grafo(numGrupos, 0, 1, 0);
    int subArvores[ordem];
    int cont = 0, contador = 0;

    //ADICIONA OS NÒS E GERA AS SUBARVORES
    for(int i = 0; i < ordem; i++)
    {
        sub[i] = getNo(to_string(i));
        subArvores[sub[i]->getOrdemDeInsercao()] = sub[i]->getOrdemDeInsercao();
    }

    //FAZ UM VETOR COM AS ARESTAS 
    for(int i = 0; i < ordem; i++)
    {
        Aresta* a = sub[i]->getPrimeiraAresta();
        while(a != NULL)
        {
            for(int j = i+1; j < ordem; j++)
            {
                if(a->getDirecaoId() == sub[j]->getId())
                {
                    arestas[cont].id = sub[i];
                    arestas[cont].idDirecao = a;
                    cont++;
                }
            }

            a = a->getProximaAresta();
        }
    }

    //ORDENA AS ARESTAS
    QuickSort(arestas, 0, cont-1);
    
    //INICIA VETOR DE GRUPOS
    for(int i = 0; i < numGrupos; i++)
    {
        pi[i] = -1;
    }

    int itensNaLista = cont + 1;
    int peso = 0;
    int num = numGrupos;

    //PERCORRE A LISTA ATÉ INSERIR numGrupos DE VÉRTICES
    //E numGrupos-1 ARESTAS 
    while(num > 1)
    {
        aresta A = arestas[0];
        //Remove a aresta 
        for(int i = 0; i < cont-1; i++)
        {
            arestas[i] = arestas[i+1];
        }
        //Diminui o número de itens
        itensNaLista--;

        //VERIFICA SE OS NÓS A SEREM INSERIDOS JÁ POSSUEM REPRESENTANTES EM SEUS DEVIDOS GRUPOS
        bool mesmoGrupo = ((pi[stoi(A.id->getGrupo())-1] == -1) || (pi[stoi(A.id->getGrupo())-1] == stoi(A.id->getId()))) && ((pi[stoi(A.idDirecao->getGrupo())-1] == -1) || (pi[stoi(A.idDirecao->getGrupo())-1] == stoi(A.idDirecao->getDirecaoId())));
        //Se os nós não estão na mesma subárvore
        if((subArvores[A.idDirecao->getOrdemDeInsercao()] != subArvores[A.id->getOrdemDeInsercao()]) && mesmoGrupo)
        {
            int maior; 
            num--;

            //Insere a aresta na solução
            T->insereAresta(A.id->getId(), A.idDirecao->getDirecaoId(), A.idDirecao->getPeso());

            peso += A.idDirecao->getPeso();
            
            //Junta as subárvores dos nós na menor e atualiza o vetor subArvores[]
            if(subArvores[A.idDirecao->getOrdemDeInsercao()] < subArvores[A.id->getOrdemDeInsercao()])
            {
                maior = subArvores[A.id->getOrdemDeInsercao()];
                subArvores[A.id->getOrdemDeInsercao()] = subArvores[A.idDirecao->getOrdemDeInsercao()];
            }else
            {
                maior = subArvores[A.idDirecao->getOrdemDeInsercao()];
                subArvores[A.idDirecao->getOrdemDeInsercao()] = subArvores[A.id->getOrdemDeInsercao()];
            }
            contador++;
            for(int i = 0; i < ordem; i++)
            {
                if(subArvores[i] == maior)
                {
                    subArvores[i] = subArvores[A.idDirecao->getOrdemDeInsercao()];
                }
            }
            if(pi[stoi(A.idDirecao->getGrupo())-1] == -1)
            {
                pi[stoi(A.idDirecao->getGrupo())-1] = stoi(A.idDirecao->getDirecaoId());
            }
            if(pi[stoi(A.id->getGrupo())-1] == -1)
            {
                pi[stoi(A.id->getGrupo())-1] = stoi(A.id->getId());
            }
        }
        
    }
    T->setPesoArvore(peso);
    cout << T->getPesoArvore() << endl;
    delete [] arestas;
    T->geraArquivoDot("ArqOut.dot", "G");
    return T->getPesoArvore();

}

//ALGORITMO GULOSO RANDOMIZADO PARA O PROLEMA DA ÁRVORE GERADORA MÍNIMA GERERALIZADA
//RETORNA O PESO DA ÁRVORE GERADA
float Grafo::arvoreMinimaGeneralizadaGulosoRandomizado(float alfa, int numIter)
{   
    No* sub[ordem];
    int pi[numGrupos+1];
    aresta *arestasCop = new aresta[numeroArestas];
    aresta* arestas = new aresta[numeroArestas];
    Grafo* melhorSolucao = new Grafo(numGrupos, 0, 1, 0);
    int subArvores[ordem];

    srand(time(NULL));
    int k = 0;
    //ADICIONA OS NÒS E GERA AS SUBARVORES
    for(int i = 0; i < ordem; i++)
    {
        sub[i] = getNo(to_string(i));
        subArvores[sub[i]->getOrdemDeInsercao()] = sub[i]->getOrdemDeInsercao();
    }

    melhorSolucao->setPesoArvore(99999999);

    int cont = 0, contador = 0;

     //FAZ UM VETOR COM AS ARESTAS 
        for(int i = 0; i < ordem; i++)
        {
            Aresta* a = sub[i]->getPrimeiraAresta();
            while(a != NULL)
            {
                for(int j = i+1; j < ordem; j++)
                {
                    if(a->getDirecaoId() == sub[j]->getId())
                    {
                        arestas[cont].id = sub[i];
                        arestas[cont].idDirecao = a;
                        cont++;
                    }
                }

                a = a->getProximaAresta();
            }
        }
    
    QuickSort(arestas, 0, cont-1);

    //COMEÇA AS ITERAÇÕES
    while(k<numIter)
    {
        int peso = 0;
        Grafo* T = new Grafo(numGrupos, 0, 1, 0);
        k++;

        //ADICIONA OS NÒS E GERA AS SUBARVORES
        for(int i = 0; i < ordem; i++)
        {
            sub[i] = getNo(to_string(i));
            subArvores[sub[i]->getOrdemDeInsercao()] = sub[i]->getOrdemDeInsercao();
        }

        //COPIA O VETOR DE ARESTAS
       for(int i = 0; i < numeroArestas; i++)
        {
            arestasCop[i] = arestas[i];
        }

        //INICIA O VETOR DE GRUPOS
        for(int i = 0; i < numGrupos; i++)
        {
            pi[i] = -1;
        }


        int itensNaLista = cont + 1;
        int num = numGrupos;
        int tam = (alfa*(numeroArestas-1));

        //PERCORRE A LISTA ATÉ INSERIR numGrupos DE VÉRTICES
        //E numGrupos-1 ARESTAS
        while(num > 1)
        {
            //ESCOLHE UM ÍNDICE ALEATÓRIO
            int indice = rand()% tam;

            aresta A = arestasCop[indice];

            //Remove a aresta 
            for(int i = indice; i < cont-1; i++)
            {
                arestasCop[i] = arestasCop[i+1];
            }
            
            //Diminui o número de itens
            itensNaLista--;

            bool mesmoGrupo = ((pi[stoi(A.id->getGrupo())-1] == -1) || (pi[stoi(A.id->getGrupo())-1] == stoi(A.id->getId()))) && ((pi[stoi(A.idDirecao->getGrupo())-1] == -1) || (pi[stoi(A.idDirecao->getGrupo())-1] == stoi(A.idDirecao->getDirecaoId())));


            //Se os nós não estão na mesma subárvore
            if((subArvores[A.idDirecao->getOrdemDeInsercao()] != subArvores[A.id->getOrdemDeInsercao()]) && mesmoGrupo)
            {
                int maior; 
                num--;

                //Insere a aresta na solção
                T->insereAresta(A.id->getId(), A.idDirecao->getDirecaoId(), A.idDirecao->getPeso());

                peso += A.idDirecao->getPeso();
                
                //Junta as subárvores dos nós na menor e atualiza o vetor subArvores[]
                if(subArvores[A.idDirecao->getOrdemDeInsercao()] < subArvores[A.id->getOrdemDeInsercao()])
                {
                    maior = subArvores[A.id->getOrdemDeInsercao()];
                    subArvores[A.id->getOrdemDeInsercao()] = subArvores[A.idDirecao->getOrdemDeInsercao()];
                }else
                {
                    maior = subArvores[A.idDirecao->getOrdemDeInsercao()];
                    subArvores[A.idDirecao->getOrdemDeInsercao()] = subArvores[A.id->getOrdemDeInsercao()];
                }
                contador++;
                for(int i = 0; i < ordem; i++)
                {
                    if(subArvores[i] == maior)
                    {
                        subArvores[i] = subArvores[A.idDirecao->getOrdemDeInsercao()];
                    }
                }
                if(pi[stoi(A.idDirecao->getGrupo())-1] == -1)
                {
                    pi[stoi(A.idDirecao->getGrupo())-1] = stoi(A.idDirecao->getDirecaoId());
                }
                if(pi[stoi(A.id->getGrupo())-1] == -1)
                {
                    pi[stoi(A.id->getGrupo())-1] = stoi(A.id->getId());
                }
            }
        }
    
        T->setPesoArvore(peso);
        //SE EXISTE UMA SOLUÇÃO MELHOR melhorSolucao RECEBE ELA
        if(T->getPesoArvore() < melhorSolucao->getPesoArvore())
        {
            melhorSolucao = T;
        }
    }
    cout << melhorSolucao->getPesoArvore() << endl;
    delete [] arestas;
    melhorSolucao->geraArquivoDot("ArqOut.dot", "G");
    return melhorSolucao->getPesoArvore();
}


float Grafo::arvoreMinimaGeneralizadaGulosoRandomizadoReativo(float alfas[], int numIter, int bloco, int tam)
{   
    No* sub[ordem];
    int pi[numGrupos+1];
    aresta* arestas = new aresta[numeroArestas];
    Grafo* melhorSolucao = new Grafo(numGrupos, 0, 1, 0);
    aresta *arestasCop = new aresta[numeroArestas];
    float P[tam];
    Media A[tam];
    int subArvores[ordem];
    int cont = 0, contador = 0;
    int alfa;

    //INICIALIZA VETORES DE PROBABILIDADE E MÉDIA
    inicializaVetores(P, A, tam);

    srand(time(NULL));
    int k = 0;

    //ADICIONA OS NÒS E GERA AS SUBARVORES
    for(int i = 0; i < ordem; i++)
    {
        sub[i] = getNo(to_string(i));
        subArvores[sub[i]->getOrdemDeInsercao()] = sub[i]->getOrdemDeInsercao();
    }

    melhorSolucao->setPesoArvore(99999999);

    //FAZ UM VETOR COM AS ARESTAS 
        for(int i = 0; i < ordem; i++)
        {
            Aresta* a = sub[i]->getPrimeiraAresta();
            while(a != NULL)
            {
                for(int j = i+1; j < ordem; j++)
                {
                    if(a->getDirecaoId() == sub[j]->getId())
                    {
                        arestas[cont].id = sub[i];
                        arestas[cont].idDirecao = a;
                        cont++;
                    }
                }

                a = a->getProximaAresta();
            }
        }


        //ORDENA AS ARESTAS
        QuickSort(arestas, 0, cont-1);

    //COMEÇA AS ITERAÇÕES
    while(k<numIter)
    {
        //VERIFICA SE ESTÁ NO BLOCO DE ITERAÇÕES 
        if(k%bloco == 0 && k != 0)
        {
            atualizaProbabilidades(P, A, melhorSolucao, tam);
        }

        //IMPEDE QUE ALGUM ALFA FIQUE SEM MÉDIA
        if(k < tam)
        {
            alfa = k;
        }
        else
        {
            //ESCOLHE UM ALFA A PARTIR DAS PROBABILIDADES
            alfa = escolheAlfa(P, tam);
        }

        int peso = 0;
        Grafo* T = new Grafo(numGrupos, 0, 1, 0);
        k++;

        //COPIA O VERTOR DE ARESTAS
        for(int i = 0; i < numeroArestas; i++)
        {
            arestasCop[i] = arestas[i];
        }

        //ADICIONA OS NÒS E GERA AS SUBARVORES
        for(int i = 0; i < ordem; i++)
        {
            sub[i] = getNo(to_string(i));
            subArvores[sub[i]->getOrdemDeInsercao()] = sub[i]->getOrdemDeInsercao();
        }

        for(int i = 0; i < numGrupos; i++)
        {
            pi[i] = -1;
        }

        int itensNaLista = cont + 1;
        int num = numGrupos;

        int tamLista = (numeroArestas-1)*alfas[alfa];
        
        //PERCORRE A LISTA ATÉ INSERIR numGrupos DE VÉRTICES
        //E numGrupos-1 ARESTAS
        while(num > 1)
        {
            //ESCOLHE UM ÍNDICE ALEATÓRIO
            int indice = rand()% tamLista;
            
            aresta A = arestasCop[indice];

            //Remove a aresta 
            for(int i = indice; i < cont-1; i++)
            {
                arestasCop[i] = arestasCop[i+1];
            }

            //Diminui o número de itens
            itensNaLista--;

            bool mesmoGrupo = ((pi[stoi(A.id->getGrupo())-1] == -1) || (pi[stoi(A.id->getGrupo())-1] == stoi(A.id->getId()))) && ((pi[stoi(A.idDirecao->getGrupo())-1] == -1) || (pi[stoi(A.idDirecao->getGrupo())-1] == stoi(A.idDirecao->getDirecaoId())));

            //Se os nós não estão na mesma subárvore
            if((subArvores[A.idDirecao->getOrdemDeInsercao()] != subArvores[A.id->getOrdemDeInsercao()]) && mesmoGrupo)
            {
                int maior; 
                num--;
                
                //Insere a aresta na solção
                T->insereAresta(A.id->getId(), A.idDirecao->getDirecaoId(), A.idDirecao->getPeso());
    
                peso += A.idDirecao->getPeso();
                
                //Junta as subárvores dos nós na menor e atualiza o vetor subArvores[]
                if(subArvores[A.idDirecao->getOrdemDeInsercao()] < subArvores[A.id->getOrdemDeInsercao()])
                {
                    maior = subArvores[A.id->getOrdemDeInsercao()];
                    subArvores[A.id->getOrdemDeInsercao()] = subArvores[A.idDirecao->getOrdemDeInsercao()];
                }else
                {
                    maior = subArvores[A.idDirecao->getOrdemDeInsercao()];
                    subArvores[A.idDirecao->getOrdemDeInsercao()] = subArvores[A.id->getOrdemDeInsercao()];
                }
            
                contador++;
                for(int i = 0; i < ordem; i++)
                {
                    if(subArvores[i] == maior)
                    {
                        subArvores[i] = subArvores[A.idDirecao->getOrdemDeInsercao()];
                    }
                }
                if(pi[stoi(A.idDirecao->getGrupo())-1] == -1)
                {
                    pi[stoi(A.idDirecao->getGrupo())-1] = stoi(A.idDirecao->getDirecaoId());
                }
                if(pi[stoi(A.id->getGrupo())-1] == -1)
                {
                    pi[stoi(A.id->getGrupo())-1] = stoi(A.id->getId());
                }
            }
        }
        T->setPesoArvore(peso);

        //ATUALIZA AS MÉDIAS PARA ALFA ESCOLHIDO
        atualizaMedias(A, T, alfas[alfa], tam, alfas);

        //SE EXISTE UMA SOLUÇÃO MELHOR melhorSolucao RECEBE ELA
        if(T->getPesoArvore() < melhorSolucao->getPesoArvore())
        {
            melhorSolucao = T;
        }
    }
    cout << melhorSolucao->getPesoArvore() << endl;
    melhorSolucao->geraArquivoDot("ArqOut.dot", "G");
    delete [] arestas;
    return melhorSolucao->getPesoArvore();
}

//RECEBE OS VETORES DE MÉDIA E PROBABILIDADE E INICIALIZA SEUS VALORES
void Grafo::inicializaVetores(float P[], Media A[], int tam)
{
    float c = 1.0/tam;
    for(int i = 0; i < tam; i++)
    {
        P[i] = c;
    }
    for(int i = 0; i < tam; i++)
    {
        A[i].media = 0;
        A[i].numSolucoes = 0;
    }
}

//RECEBE OS VETORES DE PROBABILIDADE E MÉDIA E A melhorSolucao 
//E ATUALIZA SEUS VALORES CONFORME OS RESULTADOS OBTIDOS
void Grafo::atualizaProbabilidades(float P[], Media A[], Grafo* melhorSolucao, int tam)
{
    float q[tam];
    float soma = 0;
    
    for(int i = 0; i < tam; i++)
    {
        if(A[i].media != 0)
        {
            q[i] = pow((melhorSolucao->getPesoArvore()/(A[i].media/A[i].numSolucoes)), 100);
        }
        soma += q[i];
    }
    
    for(int i = 0; i < tam; i++)
    {
        P[i] = (float(q[i])/float(soma));
    } 
    
}

//RECEBE O VETOR DE MÉDIAS O ALFA ESCOLHIDO E A SOLUÇÃO ENCONTRADA
//E ATUALIZA A MÉDIA NA POSIÇÃO DO ALFA ESCOLHIDO COM A POSIÇÃO ENCONTRADA 
void Grafo::atualizaMedias(Media A[], Grafo *solucao, float alfa, int tam, float alfas[])
{
    //cout << "ALFA:" << alfa << endl;
    int i = 0;
    for(i = 0; i < tam; i++)
    {
        if(alfas[i] == alfa)
            break;
    } 
    A[i].numSolucoes++;
    A[i].media = (A[i].media + solucao->getPesoArvore());
}

//COM BASE NO VETOR DE PROBABILIDADES, ESCOLHE UM ALFA PARA SER UTILIZADO
int Grafo::escolheAlfa(float P[], int tam)
{
    srand(time(NULL));
    
    int r = rand()%1000;
    int i = 0;
    int s = 0;
    for (i=0; i<tam; ++i)
    {
        s = s + P[i]*1000;
        if(s >= r) 
        {
            return i;
        }
    }
    return i;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

//IMPLEMENTAÇÃO DO QUICKSORT

void Grafo::QuickSort(aresta sub[], int p, int q)
{
    //Verificando se o início é maior que o final
    if (p < q)
    {
        //Começando o particionamento para iniciar o valor de j
        int j = particionamento(sub, p, q);
        //Chamadas recursivas para dividir a lista e particioná-la
        QuickSort(sub, p, j - 1);
        QuickSort(sub, j + 1, q);
    }
}

int Grafo::particionamento(aresta sub[], int p, int q)
{
    int i = p - 1, j = q;
    //Escolhe o ponteiro
    int v = sub[q].idDirecao->getPeso();

    while (1)
    {
        //Percorrer o vetor até encontrar um elemento menor do que o pivô
        while (sub[++i].idDirecao->getPeso() < v);
        //Percorrer o vetor até encontrar um elemento maior do que o pivô
        while (v < sub[--j].idDirecao->getPeso())
        {
            if (j == p)
                break;
        }
        //Se os índices i e j se cruzarem o programa para
        if (i >= j)
            break;
        //Troca o elemento da esquerda com o da direita
        troca(&sub[i], &sub[j]);
    }
    //Troca o elemento da esquerda com o último elemento
    troca(&sub[i], &sub[q]);

    return i;
}

void Grafo::troca(aresta *a, aresta *b)
{
    //Criando variável auxiliar
    aresta aux = *a;
    *a = *b;
    *b = aux;
}