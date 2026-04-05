#ifndef SISTEMA_RECOMENDACAO_H
#define SISTEMA_RECOMENDACAO_H

#include <vector>
#include <string>
#include <map>
#include <list>
#include <stdio.h>
#include <tuple>

using namespace std;

typedef struct {
    char data[20];
    char codigoCliente[50];
    char codigoProduto[50];
    char nomeProduto[150];
} Dados;

struct Estruturas {
    vector<string> vetorClientes;
    map<string, int> mapaClientes;
    vector<string> vetorProdutos;
    map<string, int> mapaProdutos;
    vector<list<int>> listaCompras;
};

struct RankProduto {
    int idProduto;
    double pontuacao;
};

bool carregarBaseDados(const char* caminhoArquivo, Estruturas& estrutura);

//Devolve vetor de strings e tupla por conta do Python (PDF)
vector<string> obterComprasDoCliente(const Estruturas& estrutura, const string& codigoBusca);

vector<vector<double>> calcularMatrizSimilaridade(const Estruturas& estrutura, bool otimizado);

vector<tuple<string, double>> obterRecomendacoes(const Estruturas& estrutura, int idxCliente, const vector<vector<double>>& S, int k);

#endif