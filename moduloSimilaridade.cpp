#include "moduloSimilaridade.h"
#include <stdio.h>

vector<vector<double>> calcularMatrizSimilaridade(const Estruturas& estrutura) {
    int n = estrutura.vetorClientes.size();
    int m = estrutura.vetorProdutos.size();

    // 1. Matriz de Compras A (n clientes x m produtos) zerada
    vector<vector<int>> A(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        // Se cliente i comprar produto com código idxProduto, marca a posição correspondente em A
        for (int idxProduto : estrutura.listaCompras[i]) {
            A[i][idxProduto] = 1;
        }
    }

    // 2. Construcao da Matriz Transposta At (m x n)
    vector<vector<int>> At(m, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            At[j][i] = A[i][j];
        }
    }

    // 3. Calculo da Matriz de Intersecao I = A x At (n x n)
    vector<vector<int>> I(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                I[i][j] += A[i][k] * At[k][j];
            }
        }
    }

    vector<vector<double>> Similaridade(n, vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++) {     
        for (int j = 0; j < n; j++) {
            if (estrutura.listaCompras[i].size() != 0) {
                Similaridade[i][j] = 1.0 - ((double)I[i][j] / estrutura.listaCompras[i].size());
            }
        }
    }
    
    return Similaridade;

}