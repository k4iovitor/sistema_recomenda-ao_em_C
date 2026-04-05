#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Converte vector (C++) pra list(py) e tuple(C++) pra tuple(py)
#include "sistema_recomendacao.h"

namespace py = pybind11;

// Variáveis globais que C++ manipula e Python acessa
Estruturas estrutura_global;
vector<vector<double>> matriz_similaridade_global;

bool carregar_python(const std::string& caminho) {
    return carregarBaseDados(caminho.c_str(), estrutura_global);
}

std::vector<std::string> buscar_compras_python(const std::string& codigoCliente) {
    return obterComprasDoCliente(estrutura_global, codigoCliente);
}

void calcular_similaridade_python(bool otimizado) {
    matriz_similaridade_global = calcularMatrizSimilaridade(estrutura_global, otimizado);
}

void imprimir_matriz_python(int limite) {

    if (limite > matriz_similaridade_global.size()) {
        limite = matriz_similaridade_global.size();
    }

    printf("\n");
    
    for (int i = 0; i < limite; i++) {
        for (int j = 0; j < limite; j++) {
            printf("%.2f\t", matriz_similaridade_global[i][j]); 
        }
        printf("\n");
    }

}
std::vector<std::tuple<std::string, double>> recomendar_python(const std::string& codigoCliente, int k) {
    auto it = estrutura_global.mapaClientes.find(codigoCliente);
    
    if (it != estrutura_global.mapaClientes.end() && !matriz_similaridade_global.empty()) {
        int idxCliente = it->second;
        return obterRecomendacoes(estrutura_global, idxCliente, matriz_similaridade_global, k);
    }
    return {}; 
}

//Integração
PYBIND11_MODULE(sistema_recomendacao_py, m) {
    m.doc() = "Módulo de Recomendação C++ via Pybind11";

    m.def("carregar", &carregar_python, "Carrega a base de dados", 
          py::arg("caminho"));
          
    m.def("buscar_compras", &buscar_compras_python, "Retorna compras de um cliente", 
          py::arg("codigo_cliente"));
          
    m.def("calcular_similaridade", &calcular_similaridade_python, "Calcula a matriz", 
          py::arg("otimizado") = true);
    
    m.def("imprimir_matriz", &imprimir_matriz_python, "Imprime a matriz de similaridade", 
        py::arg("limite"));

    m.def("recomendar_produtos", &recomendar_python, "Retorna os k produtos recomendados", 
          py::arg("codigo_cliente"), py::arg("k"));
}