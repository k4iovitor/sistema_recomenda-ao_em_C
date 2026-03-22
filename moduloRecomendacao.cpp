#include "sistema_recomendacao.h"
#include <algorithm>

bool compararRank(const RankProduto &a, const RankProduto &b) {
    return a.pontuacao < b.pontuacao;
}

void recomendarProdutos(const Estruturas& estrutura, int idxCliente, const vector<vector<double>>& S, int k) {
    int totalProdutos = estrutura.vetorProdutos.size();
    int totalClientes = estrutura.vetorClientes.size();

    // PASSO 1: Lista de Vizinhos
    vector<int> L; 
    for (int s = 0; s < totalClientes; s++) {
        // Similaridade menor que 1.0 e que não seja o próprio cliente
        if (s != idxCliente && S[idxCliente][s] < 1.0) {
            L.push_back(s);
        }
    }

    // PASSO 2: Inicialização do Vetor de Ranqueamento
    vector<double> R(totalProdutos, 1.0);

    // (Estrutura para saber o que o cliente 'c' já comprou)
    vector<bool> jaComprou(totalProdutos, false);
    for (int idxProduto : estrutura.listaCompras[idxCliente]) {
        jaComprou[idxProduto] = true;
    }

    // PASSO 3: Cálculo do Ranqueamento
    for (int s : L) { 
        for (int p : estrutura.listaCompras[s]) {
            if (!jaComprou[p]) {
                R[p] = R[p] * S[idxCliente][s]; 
            }
        }
    }

    // PASSO 4: Ordenação e Seleção
    // Converte o vetor R para uma lista, a ordena e retorna os k primeiros produtos
    vector<RankProduto> vetorRanqueamento;
    for (int p = 0; p < totalProdutos; p++) {
        if (R[p] < 1.0) {
            RankProduto rp;
            rp.idProduto = p;
            rp.pontuacao = R[p];
            vetorRanqueamento.push_back(rp);
        }
    }

    std::sort(vetorRanqueamento.begin(), vetorRanqueamento.end(), compararRank);

    // --- Exibição dos Resultados ---
    printf("--- Top %d Recomendacoes para o cliente [%s] ---\n", k, estrutura.vetorClientes[idxCliente].c_str());
    
    if (vetorRanqueamento.empty()) {
        printf("  Nao ha dados suficientes na vizinhanca para gerar recomendacoes.\n");
        return;
    }
    
    for (int i = 0; i < k && i < vetorRanqueamento.size(); i++) {
        int idPro = vetorRanqueamento[i].idProduto;
        printf("  %dº) %s\n", i + 1, estrutura.vetorProdutos[idPro].c_str());
    }
}