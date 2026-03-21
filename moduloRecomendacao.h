#ifndef MODULO_RECOMENDACAO_H
#define MODULO_RECOMENDACAO_H

#include "moduloListaCompras.h"
#include <vector>
#include <string>

using namespace std;

struct produtoRanqueado {
    int idInternoProd;
    double score;
};

void recomendarAoCliente(Estruturas& estrutura, const string& codigoCliente, int k, const vector<vector<double>>& matrizSimilaridade);

#endif