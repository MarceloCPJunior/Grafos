#include <stdlib.h>
#include <stdio.h>

typedef struct Ligacao{
    int numero;
    struct Ligacao *proximo;
}Ligacao;

typedef struct No{
    int numero;
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

void matrizAdjacencia(Lista *lista){
    int tam = lista->tam;
    int matriz[tam][tam];

    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            if(i == j){
                matriz[i][j] = 1;
            }else{
                matriz[i][j] = 0;
            }
        }
    }
    
    No *no = lista->inicio;

    printf("  ");
    for(int i = 0; i < tam; i++){
        
        Ligacao *ligacao = no->inicio;

        while(ligacao != NULL){
            int cont = 0;
            No *no2 = lista->inicio;

            while(no2->numero != ligacao->numero){
                cont++;
                no2 = no2->proximo;
            }
            matriz[i][cont] = 1;
            ligacao = ligacao->proximo;
        }
        printf("%d ", no->numero);
        no = no->proximo;
    }

    no = lista->inicio;

    printf("\n");
    for (int i = 0; i < tam; i++){
        printf("%d ", no->numero);
        for (int j = 0; j < tam; j++){
            printf("%d ",  matriz[i][j]);
        }
        printf("\n");
        no = no->proximo;
    }
}

int main(){
    Lista lista;
    lista.inicio = NULL;
    lista.tam = 0;

    int qtdF, qtdP;
    int num1, num2;

    printf("Digite seu o número de funcionários e pares: ");
    scanf("%d %d", &qtdF, &qtdP);

    printf("Ligações:\n");
    for(int i = 1; i <= qtdP; i++){
        printf("-> ");
        scanf("%d %d", &num1, &num2);

        inserir(&lista, num1);
        inserirLigacao(&lista, num1, num2);

        inserir(&lista, num2);
        inserirLigacao(&lista, num2, num1);
    }
    
    listaAdjacencia(&lista);
    printf("\n\n");
    matrizAdjacencia(&lista);

    printf("\n");
    return 0;
}