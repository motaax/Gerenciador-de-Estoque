#include <stdio.h>

typedef struct {
    int codigo;
    char nome[16];
    float preco;
    int quantidade;
} Produto;

int main() {
    Produto estoque[5];
    int codigoPedido, qtdPedido, encontrado;

    //Cadastrando os produtos
    for(int i = 0; i < 5; i++) {
        printf("\nProduto: %d\n", i + 1);

        printf("Codigo: ");
        scanf("%d", &estoque[i].codigo);

        printf("Nome: ");
        scanf(" %[^\n]", estoque[i].nome);

        printf("Preco: ");
        scanf("%f", &estoque[i].preco);

        printf("Quantidade: ");
        scanf("%d", &estoque[i].quantidade);
    }

    //Pedidos
    for(;;) {
        printf("Digite o codigo do produto(0 para sair): ");
        scanf("%d", &codigoPedido);

        if(codigoPedido == 0) {
            break;
        }

        printf("Quantidade desejada: ");
        scanf("%d", &qtdPedido);

        encontrado = 0;
        for(int i = 0; i < 5; i++) {
            if(estoque[i].codigo == codigoPedido) {
                encontrado = 1;

                if(estoque[i].quantidade >= qtdPedido) {
                    estoque[i].quantidade -= qtdPedido;
                    printf("Pedido atendido! \n");
                    printf("Estoque restante: %d \n", estoque[i].quantidade);
                } else {
                    printf("Erro: estoque insuficiente. \n");
                }

                break;
            }
        }

        if(encontrado == 0) {
            printf("Erro: codigo nao encontrado. \n");
        }
    }

    return 0;
}