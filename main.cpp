#include <iostream>  
#include <iomanip>  
#include <cstring>
#include <fstream>
#include <ctype.h>
#include <ctime>
#include "Grafo.h"

using namespace std;

Grafo* lerArquivoEntrada(string arquivoEntrada, bool direcionado, bool pesoArestas, bool pesoNos)
{
    int ordem;
    ifstream entrada;

    //Abre arquivo de entrada
    entrada.open(arquivoEntrada);

    //Verifica se o arquivo foi aberto
    if(entrada.is_open())
    {
        string str;

        //Pega uma linha do arquivo
        getline(entrada, str);

        ordem = stoi(str);

        //Cria o grafo com as informações 
        Grafo* G = new Grafo(ordem, direcionado, pesoArestas, pesoNos);

        //Insere os nós no grafo com base na ordem
        //for(int i = 1; i <= ordem; i++)
        //{
           // G.insereNo(i);
        //}

        //Lê o arquivo até o final pára encontrar as arestas entre os nós
        while (!entrada.eof())
        {
            getline(entrada, str);
            if(str != "")
            {
                int pos = str.find(' ');

                /*Recupera os nós e o peso das arestas, atribui a substring até a posição do espaço que 
                separa os nós e o peso e corta a string até essa posição */ 
                string noUm = str.substr(0, pos);
                str.erase(0, pos+1);
                pos = str.find(' ');
                string noDois = str.substr(0, pos);
                int peso = 0;
                if(pesoArestas)
                {
                    str.erase(0, pos+1);
                    if(pos == -1)
                    {
                        cout << "Falta peso no arquivo" << endl;
                        exit(4);
                    }
                    peso = stoi(str);
                }
     
                //Insere a aresta, caso exista um peso adiciona-o.
                G->insereAresta(noUm, noDois, peso);
            }
            
        }
        return G;
        
    }
    else
    {
        cout << "Erro ao abrir arquivo" << endl;
        exit(2);
    }
}

Grafo* lerInstancia(string instancia)
{
    ifstream arquivoInstancia;

    Grafo* G = new Grafo();

    int i = 0;
    int numGrupos = -1;

    //Abre arquivo de instancia
    arquivoInstancia.open(instancia);

    if(arquivoInstancia.is_open())
    {
        bool aresta = 0;
        while(!arquivoInstancia.eof())
        {
            string str;
            getline(arquivoInstancia, str);

            if(str == "")
            {
                aresta = 1;
                continue;
            }
            
            if(!aresta)
            {
                G->insereNo(to_string(i));
                G->getNo(to_string(i))->setGrupo(str);
                if(numGrupos < stoi(str))
                {
                    numGrupos = stoi(str);
                    G->setNumGrupos(stoi(str));
                }
                i++;
            }
            else
            {
                int pos = str.find(' ');

                /*Recupera os nós e o peso das arestas, atribui a substring até a posição do espaço que 
                separa os nós e o peso e corta a string até essa posição */ 
                string noUm = str.substr(0, pos);
                str.erase(0, pos+1);
                pos = str.find(' ');
                string noDois = str.substr(0, pos);
                int peso = 0;
                str.erase(0, pos+1);
                if(pos == -1)
                {
                    cout << "Falta peso no arquivo" << endl;
                    exit(4);
                }
                peso = stoi(str);
     
                //Insere a aresta, caso exista um peso adiciona-o.
                G->insereAresta(noUm, noDois, peso);
            }
        }
    }
    else
    {
        cout << "Falha ao abrir arquivo!" << endl;
        exit(10);
    }

    G->setOrdem(i);
    cout << endl;
    return G;
}


int main(int argc, char **argv)
{  
    string algoritmo = argv[1];
    string instancia(argv[2]);

    Grafo* G = lerInstancia(instancia);
    clock_t start, end;
    double time_taken = 0;
    
    if(algoritmo == "0")
    {
        start = clock();
        G->arvoreMinimaGeneralizadaGuloso();
        end = clock();
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time: " << fixed << setprecision(5) << time_taken;
        cout << " sec " << endl;
    }
    else if(algoritmo == "1")
    {
        float alfa;
        int iteracoes;
        cout << "Escolha quantidade de iteracoes:";
        cin >> iteracoes;
        cout << "Escolha alfa:";
        cin >> alfa; 
        time_taken = 0;
        start = clock();
        G->arvoreMinimaGeneralizadaGulosoRandomizado(alfa, iteracoes);
        end = clock();
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time: " << fixed << setprecision(5) << time_taken;
        cout << " sec " << endl;
    }else if(algoritmo == "2")
    {
        float alfa;
        int quantAlfas;
        int iteracoes;
        cout << "Escolha quantidade de iteracoes:";
        cin >> iteracoes;
        int bloco;
        cout << "Escolha o bloco:";
        cin >> bloco;
        cout << "Escolha quantidade de alfas:";
        cin >> quantAlfas;
        float alfas[quantAlfas];
        for(int i = 0; i < quantAlfas; i++)
        {
            cout << "Escolha o alfa " << i << ":";
            cin >> alfas[i];
        }
        time_taken = 0;
        start = clock();
        G->arvoreMinimaGeneralizadaGulosoRandomizadoReativo(alfas, iteracoes, bloco, quantAlfas);
        end = clock();
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time: " << fixed << setprecision(5) << time_taken;
        cout << " sec " << endl;
    }
    return 0;
}
