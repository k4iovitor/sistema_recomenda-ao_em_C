#include "moduloRecomendacao.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Função usada para ordenar os produtos.
bool compararScore(const produtoRanqueado& a, const produtoRanqueado& b) {
    return a.score < b.score; // Ordem crescente: menores valores são melhores para recomendar
}

void recomendarAoCliente(Estruturas& estrutura, const string& codigoCliente, int k, const vector<vector<double>>& matrizSimilaridade) {
    
    // Verifica se o cliente digitado pelo usuário realmente existe no mapa
    if (estrutura.mapaClientes.find(codigoCliente) == estrutura.mapaClientes.end()) {
        printf("Cliente %s nao encontrado!\n", codigoCliente.c_str());
        return; // Encerra a função imediatamente se o cliente não existir
    }

    // Resgata os IDs de cliente
    int idCliente = estrutura.mapaClientes[codigoCliente];

    int totalProdutos = estrutura.vetorProdutos.size();
    int totalClientes = estrutura.vetorClientes.size();

    vector<int> L; // Vetor que guardará o ID dos clientes parecidos
    for (int vizinho = 0; vizinho < totalClientes; vizinho++) {
        // É vizinho se NÃO for o próprio cliente alvo (s != idCliente)
        // E se a distância matemática entre eles for menor que 1.0
        if (vizinho != idCliente && matrizSimilaridade[idCliente][vizinho] < 1.0) {
            L.push_back(vizinho); // Adiciona o vizinho na lista L
        }
    }

    // Cria um vetor 'R' contendo uma associação (indice do produto, pontuação) para todos os produtos da loja
    vector<produtoRanqueado> R(totalProdutos);

    // Preenche o vetor
    for (int p = 0; p < totalProdutos; p++) {
        R[p].idInternoProd = p;
        R[p].score = 1.0; // Todos começam com a nota máxima (distância máxima)
    }

    // Perpassa por cada vizinho que encontramos
    for (int vizinho : L) {
        // Passa por cada produto que esse vizinho comprou
        for (int p : estrutura.listaCompras[vizinho]) {
            
            // Procura se esse produto 'p' do vizinho já foi comprado pelo nosso cliente alvo
            auto it = std::find(estrutura.listaCompras[idCliente].begin(), estrutura.listaCompras[idCliente].end(), p);
            
            // Se o 'find' chegar no final (.end()), significa que o cliente AINDA NÃO comprou o produto
            if (it == estrutura.listaCompras[idCliente].end()) {
                // Atualiza o score multiplicando ele pela distância do vizinho (efeito cumulativo)
                // Isso faz a nota diminuir (ficar melhor) a cada vizinho que comprou o item
                R[p].score = R[p].score * matrizSimilaridade[idCliente][vizinho];
            }
        }
    }

    // Reorganiza o vetor R do menor score (melhor) para o maior score (pior)
    std::sort(R.begin(), R.end(), compararScore);

    printf("\n--- Top %d recomendacoes para o cliente %s ---\n", k, codigoCliente.c_str());
    
    int exibidos = 0; // Contador de quantos produtos já foi mostrado na tela
    
    // Condição para se acabar os produtos da loja (i < totalProdutos) 
    // OU se bater a meta de recomendações pedida pelo usuário (exibidos < k)
    for (int i = 0; i < totalProdutos && exibidos < k; i++) {
        
        // Só recomenda produtos cujo score diminuiu.
        // Se o score for 1.0, significa que NENHUM vizinho comprou ele, logo é irrelevante.
        if (R[i].score < 1.0) {
            int idOriginal = R[i].idInternoProd; // Resgata o ID original do produto para buscar o nome dele
            
            // Imprime no console: [Posição]. [Nome do Produto] (Score: [Nota])
            printf("%d. %s (Score: %.6f)\n", exibidos + 1, estrutura.vetorProdutos[idOriginal].c_str(), R[i].score);
            
            exibidos++; // Avisa que conseguimos imprimir mais um
        }
    }

    // Se o laço terminou e o contador continuou no zero
    if (exibidos == 0) {
        printf("- Nenhuma recomendacao encontrada baseada nos vizinhos.\n");
    }
}