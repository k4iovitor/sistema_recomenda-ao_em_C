#include <stdio.h>
#include <string>
#include "sistema_recomendacao.h"

int main() {
    Estruturas estrutura;

    if (!carregarBaseDados("dados_venda_inicial/dados_venda_cluster_0.csv", estrutura)) {
        return 1;
    }

    printf("Arquivo carregado!\n");

    //ATIVIDADE 2 e 4
    int tamanhoMatriz;
    bool otimizado;

    printf("\nPrefere calcular a matriz de forma otimizada? (1 para sim, 0 para nao)\n");
    scanf("%d", &otimizado);

    vector<vector<double>> matrizSimilaridade = calcularMatrizSimilaridade(estrutura, otimizado);

    printf("\nInsira tamanho da Matriz de Similaridade\n");
    scanf("%d", &tamanhoMatriz);

    printf("\nMatriz de Similaridade de tamanho %d:\n", tamanhoMatriz);

    for (int i = 0; i < tamanhoMatriz; i++) {
        for (int j = 0; j < tamanhoMatriz; j++) {
            printf("%.2f\t", matrizSimilaridade[i][j]); 
        }
        printf("\n");
    }

    //ATIVIDADE 1 E 3
    for (int i = 0; i < 3; i++) {
        
        char codigoCliente[10];
    
        printf("\nDigite o codigo do cliente: \n");
        scanf("%s", codigoCliente);

        auto it = estrutura.mapaClientes.find(string(codigoCliente));
        if (it != estrutura.mapaClientes.end()) {

            exibirComprasDoCliente(estrutura, string(codigoCliente));

            int k;
            printf("\nQuantos produtos deseja recomendar? ");
            scanf("%d", &k);

            int idxCliente = it->second;
            recomendarProdutos(estrutura, idxCliente, matrizSimilaridade, k);
        } else {
            printf("Cliente nao encontrado.\n");
        }

    }

    return 0;

}