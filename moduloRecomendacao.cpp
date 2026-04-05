#include "sistema_recomendacao.h"
#include <algorithm>

bool compararRank(const RankProduto &a, const RankProduto &b) {
    return a.pontuacao < b.pontuacao;
}

vector<tuple<string, double>> obterRecomendacoes(const Estruturas& estrutura, int idxCliente, 
                                                    const vector<vector<double>>& S, int k) {
    int totalProdutos = estrutura.vetorProdutos.size();
    int totalClientes = estrutura.vetorClientes.size();
    
    //Lista de Vizinhos
    vector<int> ListaVizinhos; 
    for (int s = 0; s < totalClientes; s++) {
        if (s != idxCliente && S[idxCliente][s] < 1.0) {
            ListaVizinhos.push_back(s);
        }
    }

    //Inicialização do Vetor de Ranqueamento
    vector<double> R(totalProdutos, 1.0);

    //Estrutura para saber o que o cliente 'c' já comprou
    vector<bool> jaComprou(totalProdutos, false);
    for (int idxProduto : estrutura.listaCompras[idxCliente]) {
        jaComprou[idxProduto] = true;
    }

    //Cálculo do Ranqueamento
    for (int s : ListaVizinhos) { 
        for (int p : estrutura.listaCompras[s]) {
            if (!jaComprou[p]) {
                R[p] = R[p] * S[idxCliente][s]; 
            }
        }
    }
    
    //Ordenação e Seleção
    //Converte o vetor R para uma lista, a ordena e retorna os k primeiros produtos
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

    vector<tuple<string, double>> resultado;
    
    for (int i = 0; i < k && i < vetorRanqueamento.size(); i++) {
        int idPro = vetorRanqueamento[i].idProduto;
        resultado.push_back(make_tuple(estrutura.vetorProdutos[idPro], vetorRanqueamento[i].pontuacao));
    }
    
    return resultado; // Retorna a lista de tuplas para o Python
}