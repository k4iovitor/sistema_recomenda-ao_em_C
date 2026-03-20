#ifndef MODULO_LISTA_COMPRAS_H
#define MODULO_LISTA_COMPRAS_H

#include <vector>
#include <string>
#include <map>
#include <list>
#include <stdio.h>

using namespace std;

// Struct que encapsula todas as estruturas de dados requeridas
struct Estruturas {
    vector<string> vetorClientes;
    map<string, int> mapaClientes;
    vector<string> vetorProdutos;
    map<string, int> mapaProdutos;
    vector<list<int>> listaCompras;
};

bool carregarBaseDados(const char* caminhoArquivo, Estruturas& estrutura);

#endif