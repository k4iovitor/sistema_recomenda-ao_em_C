#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Inclusão dos outros arquivos
#include "moduloListaCompras.cpp"
#include "estruturas.h"

using namespace std;

int main(){

    // Vetores dinâmicos que guardarão os códigos em texto sem duplicatas.
    vector<string> vetorClientes;
    vector<string> vetorProdutos;

    // Estruturas de dicionário para ligar o texto do código a uma posição (índice) inteira.
    map<string, int> mapaClientes;
    map<string, int> mapaProdutos;

    // Um vetor onde cada posição representa um cliente.
    // Dentro de cada posição, há uma 'lista' de inteiros com os índices dos produtos que ele comprou.
    vector<list <int>> listaCompras;

    FILE *arquivo;
    Dados dados; // Instância da struct que criamos em estruturas.h

    // Abre o arquivo de dados em modo de leitura
    // Certifique-se de que o caminho "../dados_venda_inicial/dados_venda_cluster_0.csv" esteja correto
    arquivo = fopen("../dados_venda_inicial/dados_venda_cluster_0.csv", "r");

    printf("Leitura dos dados do arquivo:\n");
    printf("------------------------------------------------------\n");

    // O arquivo tem uma primeira linha de cabeçalho
    // Usamos o fgets apenas para "ler e jogar fora" essa primeira linha, para o fscanf não bugar.
    char cabecalho[200];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // Passo 1: Varre o arquivo para mapear todo mundo que existe
    criaClienteProduto(arquivo, dados.data, dados.codCliente, dados.codProduto, dados.nomeProduto, vetorClientes, vetorProdutos, mapaClientes, mapaProdutos);

    // Agora que sabemos exatamente quantos clientes únicos existem, redimensionamos
    // o vetor de compras para ter exatamente esse tamanho.
    listaCompras.resize(vetorClientes.size());

    // Como já lemos o arquivo inteiro no passo 1, o ponteiro de leitura está lá no final.
    // clearerr limpa possíveis erros de "fim de arquivo" (EOF).
    clearerr(arquivo);
    // rewind "rebobina" o arquivo, voltando o ponteiro de leitura para a primeira linha.
    rewind(arquivo);
    
    // Como voltamos pro começo, precisamos ignorar a linha de cabeçalho de novo.
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // Passo 2: Varre o arquivo novamente. Agora montando a matriz de quem comprou o quê.
    preencheListaCompras(arquivo, dados.data, dados.codCliente, dados.codProduto, dados.nomeProduto, mapaClientes, mapaProdutos, listaCompras);

    // Fechar o arquivo após terminar de usá-lo.
    fclose(arquivo);
    
    return 0;
}