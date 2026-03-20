#include "moduloListaCompras.h"
#include "dadosCSV.h"

// Retorna 'true' se deu certo e 'false' se houver erro na leitura
bool carregarBaseDados(const char* caminhoArquivo, Estruturas& estrutura) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", caminhoArquivo);
        return false;
    }

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), arquivo); // Pula a primeira linha

    Dados dados;
    
    //Mapeamento de Clientes e Produtos
    while (fscanf(arquivo, "%[^,],%[^,],%[^,],%[^\n]\n",
        dados.data, dados.codigoCliente, dados.codigoProduto, dados.nomeProduto) == 4) {
        
        //transforma a string estilo C (char[]) em uma std::string do C++, exigida pelo map.
        string sCodCli(dados.codigoCliente);
        
        /*Procura se o código do cliente já existe no mapa, até o final do mapa
        Se for novo, cria um "ID interno" considerando o tamanho atual do vetor (primeiro-0, segundo-1, etc).*/
        if (estrutura.mapaClientes.find(sCodCli) == estrutura.mapaClientes.end()) {
            estrutura.mapaClientes[sCodCli] = estrutura.vetorClientes.size();
            estrutura.vetorClientes.push_back(sCodCli);
        }

        string sCodPro(dados.codigoProduto);
        if (estrutura.mapaProdutos.find(sCodPro) == estrutura.mapaProdutos.end()) {
            estrutura.mapaProdutos[sCodPro] = estrutura.vetorProdutos.size();
            estrutura.vetorProdutos.push_back(string(dados.nomeProduto));
        }
    }
    fclose(arquivo); 
    
    //Preenchimento da Lista de Compras
    estrutura.listaCompras.resize(estrutura.vetorClientes.size());

    arquivo = fopen(caminhoArquivo, "r");
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    while (fscanf(arquivo, "%[^,],%[^,],%[^,],%[^\n]\n", 
        dados.data, dados.codigoCliente, dados.codigoProduto, dados.nomeProduto) == 4) {

        // Resgata os índices sabendo o código
        int idxCli = estrutura.mapaClientes[string(dados.codigoCliente)];
        int idxPro = estrutura.mapaProdutos[string(dados.codigoProduto)];

        /*Pega o ID interno do produto e o anexa ao final de uma lista correspondente a um vetor, 
        onde o índice do vetor é o ID interno do cliente */
        estrutura.listaCompras[idxCli].push_back(idxPro);
    }

    fclose(arquivo);
    
    return true;
}