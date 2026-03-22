#include "sistema_recomendacao.h"
#include <stdio.h>

void exibirComprasDoCliente(const Estruturas& estrutura, const string& codigoBusca) {
    
    int idxCliente = estrutura.mapaClientes.find(codigoBusca) -> second; 
    
    if (estrutura.listaCompras[idxCliente].empty()) {
        printf("- Nenhum produto registado.\n");
    } else {
        printf("O cliente comprou:\n");
        for (int idxProduto : estrutura.listaCompras[idxCliente]) {
            printf("  - %s\n", estrutura.vetorProdutos[idxProduto].c_str());
        }
    }

}