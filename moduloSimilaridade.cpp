#include "sistema_recomendacao.h"
#include <ctime>

vector<vector<double>> calcularMatrizSimilaridade(const Estruturas& estrutura, bool otimizado) {
    int n = estrutura.vetorClientes.size();
    int m = estrutura.vetorProdutos.size();

    clock_t inicio = clock();

    // 1. Matriz de Compras A (n clientes x m produtos)
    vector<vector<int>> A(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int idxProduto : estrutura.listaCompras[i]) {
            A[i][idxProduto] = 1;
        }
    }

    // 2. Matriz de Interseção I (n x n)
    vector<vector<int>> I(n, vector<int>(n, 0));

    if (!otimizado) {
        // --- Algoritmo Padrão (A x At) ---
        vector<vector<int>> At(m, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                At[j][i] = A[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    I[i][j] += A[i][k] * At[k][j];
                }
            }
        }
    } else {
        // --- Algoritmo Otimizado (Explorando Simetria) ---
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int soma = 0;
                for (int k = 0; k < m; k++) {
                    soma += A[i][k] * A[j][k];
                }
                I[i][j] = soma;
                I[j][i] = soma;
            }
        }
    }

    vector<vector<double>> Similaridade(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {     
        for (int j = 0; j < n; j++) {
            if (estrutura.listaCompras[i].size()> 0) {
                Similaridade[i][j] = 1.0 - ((double)I[i][j] / estrutura.listaCompras[i].size());
            }
        }
    }

    clock_t fim = clock();
    double tempo_segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("-> Tempo de execucao: %.4f segundos.\n\n", tempo_segundos);

    return Similaridade;
}