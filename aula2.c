#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

typedef struct SubLista{
    int numero;
    struct SubLista *proximo;
}subLista;

typedef struct Lista{
    bool verificado;
    int numero;
    subLista *subL;
    struct Lista *proximo;
} lista;

void *aloca(size_t tamanho){
    void *memoria = malloc(tamanho);
    if(memoria == NULL){
        printf("Sem memória suficiente!");
        exit(1);
    }
    return memoria;
}

void incrementaSubLista(subLista **SubList, subLista *subList, int num){
    while(subList != NULL){
        if(subList->numero == num){
            return;
        }
        subList = subList->proximo;
    }

    subLista *nova = aloca(sizeof(*nova));
    nova->numero = num;
    nova->proximo = *SubList;
    *SubList = nova;
}

void incrementaLista(lista **Lista, lista *list, int num1, int num2){
    while(list != NULL){
        if(list->numero == num1){
            incrementaSubLista(&list->subL, list->subL, num2);
            return;
        }
        list = list->proximo;
    }

    lista *nova = aloca(sizeof(*nova));
    nova->numero = num1;
    nova->verificado = false;
    nova->proximo = *Lista;
    *Lista = nova;

    incrementaSubLista(&nova->subL, nova->subL, num2);
}

void exibir(lista *list){
    printf("\n");
    while(list != NULL){
        printf("Ponto: %d - Ligado com: ", list->numero);

        subLista *subList = list->subL;
        while(subList != NULL){
            printf("%d ", subList->numero);
            subList = subList->proximo;
        }
        list = list->proximo;
        printf("\n");
    }
}

void verificacao(lista *list, int num){
    lista *aux = list;

    if(aux->verificado == true){
        return;
    }else{
        aux->verificado = true;
        while(aux != NULL){
            if(aux->numero == num){
                while(aux->subL != NULL){
                    verificacao(list, aux->subL->numero);
                    aux->subL = aux->subL->proximo;
                }
            }
            aux = aux->proximo;
        }
    }

    
}

void conexoes(lista *list){
    int qtdConexoes = 0;

    while(list != NULL){
        subLista *subList = list->subL;

        while(subList != NULL){
            verificacao(list, subList->numero);
            subList = subList->proximo;
        }
        if(list->verificado == 0){
            qtdConexoes++;
        }
        list = list->proximo;
    }

    printf("\nQuantidade de conexões: %d", qtdConexoes);
}

int main(){
    lista *list = NULL;
    lista *aux = NULL;
    int qtdPares, num1, num2;

    printf("Digite a quantidade de pares: ");
    scanf("%d", &qtdPares);
    printf("\n");

    for(int i = 1; i <= qtdPares; i++){
        printf("Par %d\n", i);
        printf("Valor 1: ");
        scanf("%d", &num1);
        printf("Valor 2: ");
        scanf("%d", &num2);

        incrementaLista(&list, list, num1, num2);
        incrementaLista(&list, list, num2, num1);
    }

    exibir(list);

    conexoes(list);
    
    printf("\n");
    return 0;
}