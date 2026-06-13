#include <stdio.h>

typedef struct {
    int codigo;
    char nome[16];
    float preco;
    int quantidade;
    int vendidos;
} Produto;

int main() {

    int n, i, j;

    printf("Quantos produtos deseja cadastrar? ");
    scanf("%d", &n);

    Produto estoque[n];

    // Cadastro dos produtos
    for(i = 0; i < n; i++) {

        printf("\n=== Produto %d ===\n", i + 1);

        for(;;) {

            int repetido = 0;

            printf("Codigo: ");
            scanf("%d", &estoque[i].codigo);

            for(j = 0; j < i; j++) {
                if(estoque[i].codigo == estoque[j].codigo) {
                    repetido = 1;
                    break;
                }
            }

            if(repetido == 0) {
                break;
            }

            printf("Erro: codigo ja cadastrado!\n");
        }

        printf("Nome: ");
        scanf(" %15[^\n]", estoque[i].nome);

        printf("Preco: ");
        scanf("%f", &estoque[i].preco);

        printf("Quantidade: ");
        scanf("%d", &estoque[i].quantidade);

        estoque[i].vendidos = 0;
    }

    int opcao;

    for(;;) {

        printf("\n========== MENU ==========\n");
        printf("1 - Vender produto\n");
        printf("2 - Repor estoque\n");
        printf("3 - Listar estoque\n");
        printf("4 - Buscar por codigo\n");
        printf("5 - Buscar por nome\n");
        printf("6 - Valor total do estoque\n");
        printf("7 - Produto mais caro e mais barato\n");
        printf("8 - Relatorio de vendas\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 0) {

            printf("Encerrando programa...\n");
            break;
        }

        else if(opcao == 1) { // Venda

            int codigo, qtd;
            int encontrado = 0;

            printf("Codigo do produto: ");
            scanf("%d", &codigo);

            printf("Quantidade desejada: ");
            scanf("%d", &qtd);

            for(i = 0; i < n; i++) {

                if(estoque[i].codigo == codigo) {

                    encontrado = 1;

                    if(estoque[i].quantidade >= qtd) {

                        float valorCompra;

                        estoque[i].quantidade -= qtd;
                        estoque[i].vendidos += qtd;

                        valorCompra =
                            estoque[i].preco * qtd;

                        printf("\nPedido atendido!\n");
                        printf("Valor da compra: R$ %.2f\n",
                               valorCompra);

                        printf("Estoque restante: %d\n",
                               estoque[i].quantidade);
                    }
                    else {
                        printf("Erro: estoque insuficiente!\n");
                    }

                    break;
                }
            }

            if(encontrado == 0) {
                printf("Codigo nao encontrado!\n");
            }
        }

        else if(opcao == 2) { // Reposição

            int codigo, qtd;
            int encontrado = 0;

            printf("Codigo do produto: ");
            scanf("%d", &codigo);

            printf("Quantidade para repor: ");
            scanf("%d", &qtd);

            for(i = 0; i < n; i++) {

                if(estoque[i].codigo == codigo) {

                    estoque[i].quantidade += qtd;

                    printf("Reposicao realizada!\n");
                    printf("Novo estoque: %d\n",
                           estoque[i].quantidade);

                    encontrado = 1;
                    break;
                }
            }

            if(encontrado == 0) {
                printf("Codigo nao encontrado!\n");
            }
        }

        else if(opcao == 3) { // Listar estoque

            printf("\n===== ESTOQUE =====\n");

            for(i = 0; i < n; i++) {

                printf("\nCodigo: %d\n",
                       estoque[i].codigo);

                printf("Nome: %s\n",
                       estoque[i].nome);

                printf("Preco: R$ %.2f\n",
                       estoque[i].preco);

                printf("Quantidade: %d\n",
                       estoque[i].quantidade);

                if(estoque[i].quantidade < 10) {
                    printf("ATENCAO: Estoque baixo!\n");
                }
            }
        }

        else if(opcao == 4) { // Buscar por código

            int codigo;
            int encontrado = 0;

            printf("Codigo: ");
            scanf("%d", &codigo);

            for(i = 0; i < n; i++) {

                if(estoque[i].codigo == codigo) {

                    printf("\nProduto encontrado:\n");
                    printf("Codigo: %d\n",
                           estoque[i].codigo);

                    printf("Nome: %s\n",
                           estoque[i].nome);

                    printf("Preco: %.2f\n",
                           estoque[i].preco);

                    printf("Quantidade: %d\n",
                           estoque[i].quantidade);

                    encontrado = 1;
                    break;
                }
            }

            if(encontrado == 0) {
                printf("Produto nao encontrado!\n");
            }
        }

        else if(opcao == 5) { // Buscar por nome

            char busca[16];
            int encontrado = 0;

            printf("Nome do produto: ");
            scanf(" %15[^\n]", busca);

            for(i = 0; i < n; i++) {

                int igual = 1;

                for(j = 0; j < 16; j++) {

                    if(busca[j] != estoque[i].nome[j]) {
                        igual = 0;
                        break;
                    }

                    if(busca[j] == '\0') {
                        break;
                    }
                }

                if(igual) {

                    printf("\nProduto encontrado:\n");
                    printf("Codigo: %d\n",
                           estoque[i].codigo);

                    printf("Nome: %s\n",
                           estoque[i].nome);

                    printf("Preco: %.2f\n",
                           estoque[i].preco);

                    printf("Quantidade: %d\n",
                           estoque[i].quantidade);

                    encontrado = 1;
                }
            }

            if(encontrado == 0) {
                printf("Produto nao encontrado!\n");
            }
        }

        else if(opcao == 6) { // Valor total do estoque

            float valorTotal = 0;

            for(i = 0; i < n; i++) {

                valorTotal +=
                    estoque[i].preco *
                    estoque[i].quantidade;
            }

            printf("Valor total do estoque: R$ %.2f\n",
                   valorTotal);
        }

        else if(opcao == 7) { // Mais caro e mais barato

            int maisCaro = 0;
            int maisBarato = 0;

            for(i = 1; i < n; i++) {

                if(estoque[i].preco >
                   estoque[maisCaro].preco) {

                    maisCaro = i;
                }

                if(estoque[i].preco <
                   estoque[maisBarato].preco) {

                    maisBarato = i;
                }
            }

            printf("\nProduto mais caro:\n");
            printf("Nome: %s\n",
                   estoque[maisCaro].nome);
            printf("Preco: %.2f\n",
                   estoque[maisCaro].preco);

            printf("\nProduto mais barato:\n");
            printf("Nome: %s\n",
                   estoque[maisBarato].nome);
            printf("Preco: %.2f\n",
                   estoque[maisBarato].preco);
        }

        else if(opcao == 8) { // Relatório de vendas

            float faturamento = 0;

            printf("\n===== RELATORIO DE VENDAS =====\n");

            for(i = 0; i < n; i++) {

                float valorProduto =
                    estoque[i].vendidos *
                    estoque[i].preco;

                faturamento += valorProduto;

                printf("\nProduto: %s\n",
                       estoque[i].nome);

                printf("Quantidade vendida: %d\n",
                       estoque[i].vendidos);

                printf("Valor arrecadado: R$ %.2f\n",
                       valorProduto);
            }

            printf("\nFaturamento total: R$ %.2f\n",
                   faturamento);
        }

        else {

            printf("Opcao invalida!\n");
        }
    }

    return 0;
}