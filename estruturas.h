// Define uma struct chamada 'Dados' para armazenar temporariamente 
// os dados lidos de cada linha do arquivo CSV.
typedef struct {
    char data[20];            // Armazena a data da transação
    char codCliente[50];      // Armazena o código identificador único do cliente
    char codProduto[50];      // Armazena o código identificador único do produto
    char nomeProduto[100];    // Armazena o nome descritivo do produto
} Dados;

