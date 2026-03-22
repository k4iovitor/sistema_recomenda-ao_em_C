#ifndef SISTEMA_RECOMENDACAO_H
#define SISTEMA_RECOMENDACAO_H

#include <vector>
#include <string>
#include <map>
#include <list>
#include <stdio.h>

using namespace std;

// --- ESTRUTURAS DE DADOS ---

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

// Estrutura para auxiliar o ranqueamento na Atividade 3
struct RankProduto {
    int idProduto;
    double pontuacao;
};


// Módulo Lista de Compras
bool carregarBaseDados(const char* caminhoArquivo, Estruturas& estrutura);

// Módulo Busca (Atividade 1)
void exibirComprasDoCliente(const Estruturas& estrutura, const string& codigoBusca);

// Módulo Similaridade (Atividade 2 e 4)
vector<vector<double>> calcularMatrizSimilaridade(const Estruturas& estrutura, bool otimizado);

// Módulo Recomendação (Atividade 3)
void recomendarProdutos(const Estruturas& estrutura, int idxCliente, const vector<vector<double>>& S, int k);

#endif