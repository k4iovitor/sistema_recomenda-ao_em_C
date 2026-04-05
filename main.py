import time
import sistema_recomendacao_py # Import do módulo em C++ compilado em .py 

def main():

    #Atividade 1
    if sistema_recomendacao_py.carregar("dados_venda_inicial/dados_venda_cluster_0.csv"):   
        print("Ficheiro carregado\n")

    #Atividade 2 e 4
    print("Prefere calcular a matriz de forma otimizada? (1 para sim, 0 para nao)");
    otimizado = int(input())

    start = time.time()
    sistema_recomendacao_py.calcular_similaridade(otimizado)
    print(f"\nTempo decorrido (Padrão): {time.time() - start:.4f} segundos\n")

    print("Insira tamanho da Matriz de Similaridade");
    tamanhoMatriz = int(input());

    sistema_recomendacao_py.imprimir_matriz(tamanhoMatriz)

    #Atividades 1 e 3
    for i in range(3):
        print("\nDigite o código do cliente: ")
        cod_cliente = str(input())

        compras = sistema_recomendacao_py.buscar_compras(cod_cliente)            

        if not compras:
            print("Cliente não encontrado.")
            continue

        print(f"\nO cliente [{cod_cliente}] comprou:")
        for produto in compras:
            print(f"  - {produto}\n")

        print("Quantos produtos deseja recomendar?")
        k = int(input())
        recomendacoes = sistema_recomendacao_py.recomendar_produtos(cod_cliente, k)

        if not recomendacoes:
            print("Não há dados suficientes na vizinhança para gerar recomendações.\n")
        else:
            print(f"\nTop {len(recomendacoes)} recomendações para o cliente [{cod_cliente}] :\n")
            for i in range(len(recomendacoes)):
                idPro, similaridade = recomendacoes[i]
                print(f"  {i+1}º) {idPro} (Similaridade: {similaridade:.4f})\n")

if __name__ == "__main__":
    main()

#Trouxe todos os prints para main.py pra facilitar leitura e C só calcular