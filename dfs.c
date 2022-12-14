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
}Lista;

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

    Ligacao *ligacao = no->inicio;

    while(ligacao != NULL){
        busca(lista, ligacao->numero);
        ligacao = ligacao->proximo;
    }
}

void dfs(Lista *lista){
    No *no = lista->inicio;
    int ligacoes = 0;

    while(no != NULL){
        if(no->verificado == 0){
            busca(&lista, no->numero);
            ligacoes++;
        }
        no = no->proximo;
    }

    printf("\n\nLiga????es: %d", ligacoes);
}

int main(){
    Lista lista;
    lista.inicio = NULL;
    lista.tam = 0;

    int qtdF, qtdP;
    int num1, num2;
    int i = 1;

    printf("Digite seu o n??mero de funcion??rios e pares: ");
    scanf("%d %d", &qtdF, &qtdP);

    printf("Liga????es:\n");
    for(int i = 1; i <= qtdP; i++){
        printf("-> ");
        scanf("%d %d", &num1, &num2);

        inserir(&lista, num1);
        inserirLigacao(&lista, num1, num2);

        inserir(&lista, num2);
        inserirLigacao(&lista, num2, num1);
    }

    while(qtdF > lista.tam){
        inserir(&lista, i);
        i++;
    }

    listaAdjacencia(&lista);

    dfs(&lista);

    printf("\n");
    return 0;
}
