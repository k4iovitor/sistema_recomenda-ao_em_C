#include "moduloBusca.h"
#include <stdio.h>

void exibirComprasDoCliente(const Estruturas& estrutura, const string& codigoBusca) {
    
    if (estrutura.mapaClientes.find(codigoBusca) != estrutura.mapaClientes.end()) {
        int idxCliente = estrutura.mapaClientes.find(codigoBusca) -> second; 
        
        if (estrutura.listaCompras[idxCliente].empty()) {
            printf("- Nenhum produto registado.\n");
        } else {
            printf("O cliente comprou:\n");
            for (int idxProduto : estrutura.listaCompras[idxCliente]) {
                printf("  - %s\n", estrutura.vetorProdutos[idxProduto].c_str());
            }
        }

    } else {
        printf("Cliente nao existe!\n");
    }

}