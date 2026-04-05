#include "sistema_recomendacao.h"

vector<string> obterComprasDoCliente(const Estruturas& estrutura, const string& codigoBusca) {
    vector<string> compras;

    auto it = estrutura.mapaClientes.find(codigoBusca);
    
    if (it != estrutura.mapaClientes.end()) {
        int idxCliente = it->second;
        for (int idxProduto : estrutura.listaCompras[idxCliente]) {
            compras.push_back(estrutura.vetorProdutos[idxProduto]);
        }
    }

    return compras;

}