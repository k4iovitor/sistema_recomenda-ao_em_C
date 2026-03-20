#ifndef DADOSCSV_H
#define DADOSCSV_H

// Define uma struct nativa do C para armazenar temporariamente 
// os dados lidos de cada linha do arquivo CSV.
typedef struct {
    char data[15];
    char codigoCliente[15];
    char codigoProduto[15];
    char nomeProduto[100];
} Dados;

#endif