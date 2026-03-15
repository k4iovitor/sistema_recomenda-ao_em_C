#include <vector>
#include <string>
#include <map>
#include <list>
#include <iostream>

using namespace std;

// Função para remover aspas duplas do nome do produto, caso tenha. 
// Isso é feito para evitar erros no momento da leitura do CSV.
void limparAspas(char *str) {
    if (str == NULL) return;
    char *src = str;
    char *dst = str;
    while (*src) {
        if (*src != '"') {
            *dst = *src; // Copia o caractere apenas se não for uma aspa dupla
            dst++;
        }
        src++;
    }
    *dst = '\0'; // Adiciona o terminador de string no final
}

// Função que verifica se um determinado código de cliente ou produto já foi inserido no seu respectivo vetor..
// Ele varre o vetor apenas até o número atual de itens inseridos (cDado).
bool verificaExistencia(bool existeCliente, vector<string>& listaDado, string codDado, int cDado){
    for(int i = 0; i < cDado; i++){
        if(listaDado[i] == codDado){
            return true; // Retorna verdadeiro se encontrou o código
        }
    }
    return false; // Retorna falso se percorreu tudo e não encontrou
}

// Adiciona um novo código ao vetor, mas apenas se a verificação anterior apontou que ele não existe.
int adicionaCod(bool existeCliente, vector<string>& listaDado, string codDado, int cDado){
    if(existeCliente == false){
        listaDado.push_back(codDado); // Insere o código no final do vetor
        return ++cDado;               // Incrementa a contagem e retorna o novo tamanho
    }
    return cDado; // Se já existia, retorna a contagem sem alterar
}

// Primeira Passagem no Arquivo: Lê o arquivo inteiro para descobrir todos os clientes 
// e produtos únicos, gerando vetores e "mapas" para cada um.
void criaClienteProduto(FILE *arq, char* data, char* codCli, char* codPro, char* nomePro, vector<string>& vetorCli, vector<string>& vetorPro, map<string, int>& mapCli, map<string, int>& mapPro){

    int cCliente, cProduto;
    cCliente = cProduto = 0; // Contadores de clientes e produtos únicos encontrados

    // Lê o arquivo linha por linha usando fscanf. A máscara "%[^,]" pega tudo até a próxima vírgula.
    // O loop continua enquanto ele conseguir ler com sucesso as 4 variáveis da linha.
    while(fscanf(arq, " %[^,], %[^,], %[^,], %[^\n]",
          data,
          codCli,
          codPro,
          nomePro) == 4){

        limparAspas(nomePro); // Garante que o nome do produto não tenha aspas sujas do CSV

        // Para a primeira linha lida, não precisamos verificar duplicidade, apenas inserimos.
        if(cCliente == 0 && cProduto == 0){
            vetorCli.push_back(codCli);
            vetorPro.push_back(codPro);
            cCliente++;
            cProduto++;
        }

        bool clienteExiste, produtoExiste;
        clienteExiste = produtoExiste = false;

        // Checa se o cliente atual já está na nossa lista. Se não estiver, adiciona.
        clienteExiste = verificaExistencia(clienteExiste, vetorCli, codCli, cCliente);
        cCliente = adicionaCod(clienteExiste, vetorCli, codCli, cCliente);

        // Checa se o produto atual já está na nossa lista. Se não estiver, adiciona.
        produtoExiste = verificaExistencia(produtoExiste, vetorPro, codPro, cProduto);
        cProduto = adicionaCod(produtoExiste, vetorPro, codPro, cProduto);
    }

    // Após ler todo o arquivo, preenchemos os mapas.
    // Eles vão associar a string do código (ex: "CLI001") a um índice numérico (ex: 0, 1, 2).
    for (size_t i = 0; i < vetorCli.size(); i++){
        mapCli[vetorCli[i]] = i; 
    }

    for (size_t i = 0; i < vetorPro.size(); i++){
        mapPro[vetorPro[i]] = i;
    }
}

// Segunda Passagem no Arquivo: Lê o arquivo novamente desde o começo.
// Agora que sabemos os índices de todos os clientes e produtos, montamos a lista de compras.
void preencheListaCompras(FILE *arq, char* data, char* codCli, char* codPro, char* nomePro, map<string, int>& mapCli, map<string, int>& mapPro, vector<list<int>>& listaCom){

    // Lê as linhas do arquivo de novo
    while(fscanf(arq, " %[^,], %[^,], %[^,], %[^\n]",
          data,
          codCli,
          codPro,
          nomePro) == 4){

        string clientCod = codCli;
        string produtoCod = codPro;

        // Ao invés de usar os códigos longos em texto, usamos o 'map' para descobrir qual o número (índice)
        // do cliente e do produto que acabamos de ler nessa linha.
        int indiceCliente = mapCli[clientCod];
        int indiceProduto = mapPro[produtoCod];

        // Vai no vetor principal na posição do cliente e adiciona o índice do produto na lista dele.
        listaCom[indiceCliente].push_back(indiceProduto);
    }

    // Imprime no console a lista de compras para visualização.
    for(size_t i = 0; i < listaCom.size(); i++){
        cout << "Cliente " << i+1 << ": ";
        for(const auto& lista: listaCom[i]){
            cout << lista << " "; // Imprime o índice numérico do produto comprado
        }
        cout << endl; // Pula linha após listar os produtos do cliente
    }
}