#include <stdlib.h>
#include <stdio.h>

typedef struct Ligacao{
    int numero;
    struct Ligacao *proximo;
}Ligacao;

typedef struct No{
    int numero;
    int verificado;
    Ligacao *inicio;
    struct No *proximo;
}No;

typedef struct {
    No *inicio;
    int tam;
    int caps;
    int ligacoes;
    struct Lista *proximo;
}Lista;

int pos_cap = 1;
int num_amigos = 0;
int ligacoes = 0;

void inserir(Lista *lista, int valor){
    No *aux = lista->inicio;

    while (aux != NULL){
        if(aux->numero == valor){
            return;
        }
        aux = aux->proximo;
    }
    
    No *novo = (No*) malloc (sizeof(No));
    novo->numero = valor;
    novo->inicio = NULL;
    novo->verificado = 0;

    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->tam++;
}

void inserirLigacao(Lista *lista, int valor, int lig){
    No *aux = lista->inicio;

    while (aux != NULL){
        if(aux->numero == valor){
            Ligacao *ligacao = aux->inicio;
            
            while(ligacao != NULL){
                if(ligacao->numero == lig){
                    return;
                }
                ligacao = ligacao->proximo;
            }

            Ligacao *novo = (Ligacao*) malloc(sizeof(Ligacao));
            novo->numero = lig;
            novo->proximo = aux->inicio;
            aux->inicio = novo;

            return;
        }
        aux = aux->proximo;
    }
}

void listaAdjacencia(Lista *lista){
    No *no = lista->inicio;

    while(no != NULL){
        printf("\n%d ligado com: ", no->numero);
        Ligacao *ligacao = no->inicio;

        while(ligacao != NULL){
            printf("%d ", ligacao->numero);
            ligacao = ligacao->proximo;
        }

        no = no->proximo;
    }
}

void busca(Lista **lista, int num){
    No *no = (*lista)->inicio;

    while(no->numero != num){
        no = no->proximo;
    }

    if(no->verificado == 1){
        return;
    }

    no->verificado = 1;
    num_amigos++;

    Ligacao *ligacao = no->inicio;

    while(ligacao != NULL){
        busca(lista, ligacao->numero);
        ligacao = ligacao->proximo;
    }
}

void dfs(Lista *lista){
    No *no = lista->inicio;

    while(no != NULL){
        if(no->verificado == 0){
            busca(&lista, no->numero);
            ligacoes++;
            pos_cap *= num_amigos;
            num_amigos = 0;
        }
        no = no->proximo;
    }
}

int main(){
    int qtdF, qtdP;
    int num1, num2;
    int z = 1;
    int qtdTeste;

    printf("Quantidade de testes: ");
    scanf("%d", &qtdTeste);

    Lista lista[qtdTeste];

    for(int j = 0; j < qtdTeste; j++){
        lista[j].inicio = NULL;
        lista[j].tam = 0;
        lista[j].proximo = NULL;  
        lista[j].caps = 1;
        lista[j].ligacoes = 0;

        printf("Digite seu o número de funcionários e pares: ");
        scanf("%d %d", &qtdF, &qtdP);

        printf("Ligações:\n");
        for(int i = 1; i <= qtdP; i++){
            printf("-> ");
            scanf("%d %d", &num1, &num2);

            inserir(&lista[j], num1);
            inserirLigacao(&lista[j], num1, num2);

            inserir(&lista[j], num2);
            inserirLigacao(&lista[j], num2, num1);
        }

        while(qtdF > lista[j].tam){
            inserir(&lista[j], z);
            z++;
        }

        dfs(&lista[j]);

        lista[j].ligacoes = ligacoes;
        lista[j].caps = pos_cap;
        ligacoes = 0;
        pos_cap = 1;
        z = 0;
    }

    for(int i = 0; i < qtdTeste; i++){
        printf("\n%d %d", lista[i].ligacoes, lista[i].caps);
    }

    printf("\n");
    return 0;
}
