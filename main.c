#include <stdio.h>

#define MAX_PRODUTOS 100
#define MAX_VENDAS 1000

typedef struct {
    int codigo;
    char nome[16];
    float preco;
    int quantidade;
    int vendidos;
} Produto;

typedef struct {
    int codigo;
    int quantidade;
    float valor;
} Venda;

int buscarCodigo(Produto e[], int n, int codigo){
    int i;
    
    for(i=0;i<n;i++)
        if(e[i].codigo == codigo) return i;
    return -1;
}

void listarEstoque(Produto e[], int n){
    int i;

    for(i=0;i<n;i++){
        printf("\nCodigo: %d\n", e[i].codigo);
        printf("Nome: %s\n", e[i].nome);
        printf("Preco: %.2f\n", e[i].preco);
        printf("Quantidade: %d\n", e[i].quantidade);
        printf("Vendidos: %d\n", e[i].vendidos);
    }
}

void valorTotal(Produto e[], int n){
    float total=0;

    int i;
    for(i=0;i<n;i++) total += e[i].preco * e[i].quantidade;
    printf("Valor total do estoque: R$ %.2f\n", total);
}

void vender(Produto e[], int n, Venda h[], int *qv){
    int codigo,qtd,pos;

    printf("Codigo: ");
    scanf("%d",&codigo);

    pos = buscarCodigo(e,n,codigo);
    if(pos==-1){
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d",&qtd);

    if(e[pos].quantidade < qtd){
        printf("Estoque insuficiente.\n");
        return;
    }

    e[pos].quantidade -= qtd;
    e[pos].vendidos += qtd;

    h[*qv].codigo = codigo;
    h[*qv].quantidade = qtd;
    h[*qv].valor = qtd * e[pos].preco;
    (*qv)++;

    printf("Venda realizada.\n");
}

void repor(Produto e[], int n){
    int codigo,qtd,pos;

    printf("Codigo: ");
    scanf("%d",&codigo);

    pos = buscarCodigo(e,n,codigo);
    if(pos==-1){
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Quantidade a repor: ");
    scanf("%d",&qtd);

    e[pos].quantidade += qtd;
}

void cadastrarNovo(Produto e[], int *n){
    if(*n >= MAX_PRODUTOS){
        printf("Limite atingido.\n");
        return;
    }

    printf("Codigo: ");
    scanf("%d",&e[*n].codigo);

    printf("Nome: ");
    scanf(" %15[^\n]", e[*n].nome);

    printf("Preco: ");
    scanf("%f",&e[*n].preco);

    printf("Quantidade: ");
    scanf("%d",&e[*n].quantidade);

    e[*n].vendidos = 0;
    (*n)++;
}

void removerProduto(Produto e[], int *n){
    int codigo,pos,i;

    printf("Codigo: ");
    scanf("%d",&codigo);

    pos = buscarCodigo(e,*n,codigo);

    if(pos==-1){
        printf("Nao encontrado.\n");
        return;
    }

    for(i=pos;i<*n-1;i++)
        e[i]=e[i+1];

    (*n)--;
}

void salvar(Produto e[], int n){
    FILE *f = fopen("estoque.txt","w");
    int i;

    if(f==NULL) return;

    for(i=0;i<n;i++)
        fprintf(f," Codigo: %d\n Nome: %s\n Preco: %.2f\n Quantidade: %d\n Vendidos: %d\n\n", e[i].codigo,e[i].nome,e[i].preco, e[i].quantidade,e[i].vendidos);

    fclose(f);
    printf("Arquivo salvo.\n");
}

int main(){

    Produto estoque[MAX_PRODUTOS];
    Venda historico[MAX_VENDAS];

    int n,i,qtdVendas=0;

    printf("Quantidade inicial de produtos: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("\nProduto %d\n",i+1);

        printf("Codigo: ");
        scanf("%d",&estoque[i].codigo);

        printf("Nome: ");
        scanf(" %15[^\n]", estoque[i].nome);

        printf("Preco: ");
        scanf("%f",&estoque[i].preco);

        printf("Quantidade: ");
        scanf("%d",&estoque[i].quantidade);

        estoque[i].vendidos = 0;
    }

    for(;;){
        int op;

        printf("\n1-Vender\n 2-Repor\n 3-Listar\n 4-Valor Total\n");
        printf("5-Cadastrar Produto\n 6-Remover Produto\n 7-Salvar\n 0-Sair\n");
        scanf("%d",&op);

        if(op==0) break;
        else if(op==1) vender(estoque,n,historico,&qtdVendas);
        else if(op==2) repor(estoque,n);
        else if(op==3) listarEstoque(estoque,n);
        else if(op==4) valorTotal(estoque,n);
        else if(op==5) cadastrarNovo(estoque,&n);
        else if(op==6) removerProduto(estoque,&n);
        else if(op==7) salvar(estoque,n);
    }

    return 0;
}