#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void printaDiv() {
    printf("\n");
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    printf("\n");
}

//* TAREFA
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

//Retorna true se a data comparada for mais antiga que a data base
bool dataMenor (Data data_comparada, Data data_base) {
    if (data_comparada.ano < data_base.ano) return true;
    else if (data_comparada.mes < data_base.mes) return true;
    else if (data_comparada.dia < data_base.dia) return true;

    return false;
}

typedef struct{
    int codigo;
    char nome[30];
    char projeto[30];
    Data inicio;
    Data termino;
    int status;
    int prioridade;
} Tarefa;

//*NO
typedef struct No{
    Tarefa * tarefa;
    struct No * proximo_no;
} No;

//*LISTA
typedef No Lista;

//Cria uma nova lista sendo nula
Lista * criaLista() {
    return NULL;
}

//Se a lista estiver vazia, retorna true
bool vaziaLista(Lista * lista) {
    if (lista == NULL) return true;
    return false;
}

//Cria um novo nó com uma dada tarefa e o insere na posição ordenado pela data de término
void insereLista(Lista ** lista, Tarefa * tarefa) {
    No * novo_no = (No *) malloc(sizeof(No));
    novo_no->tarefa = tarefa;
    novo_no->proximo_no = NULL;
    Lista * no_atual = *lista;

    //Insere no início
    if (vaziaLista(no_atual) || dataMenor(tarefa->termino, no_atual->tarefa->termino)) {
        novo_no->proximo_no = no_atual;
        (*lista) = novo_no;
    } 

    //Insere da posição 1 pra frente
    else {
        while(no_atual->proximo_no != NULL && dataMenor(no_atual->tarefa->termino, tarefa->termino)) {
            no_atual = no_atual->proximo_no;
        }

        novo_no->proximo_no = no_atual->proximo_no;
        no_atual->proximo_no = novo_no;
    }
}

//printa todos os detalhes da tarefa
void printaTarefa(Tarefa tarefa) {
    printaDiv();
    printf("TAREFA \"%s\":\n\n", tarefa.nome);
    printf("Projeto: \"%s\";\n", tarefa.projeto);
    printf("Data de Início: %02d/%02d/%04d;\n", tarefa.inicio.dia, tarefa.inicio.mes, tarefa.inicio.ano);
    printf("Data de Término: %02d/%02d/%04d;\n", tarefa.termino.dia, tarefa.termino.mes, tarefa.termino.ano);
    printf("Status: %d;\n", tarefa.status);
    printf("Prioridade: %d;\n", tarefa.prioridade);
    printf("Código: %d;", tarefa.codigo);
    printaDiv();
}

//Printa todos os codigos da lista seguindo a ordem 
void printaLista(Lista * lista) {
    if (!vaziaLista(lista)) {
        while (!vaziaLista(lista)) {
            printaTarefa(*(lista->tarefa));
            lista = lista->proximo_no;
        }
    }
}

//*FILA
typedef struct {
    No * inicio;
    No * fim;
} Fila;
    
//Cria uma nova fila com o início e o fim nulos
Fila * criaFila() {
    Fila * nova_fila = (Fila *) malloc(sizeof(Fila));
    nova_fila->fim = NULL;
    nova_fila->inicio = NULL;

    return nova_fila;
}

//Se a fila estiver vazia, retorna true
bool vaziaFila(Fila * fila) {
    if (fila->inicio == NULL) return true;
    return false;
}

//Cria um novo nó com uma dada tarefa e o insere na fila
void insereFila(Fila * fila, Tarefa * tarefa) {
    No * novo_no = (No *) malloc(sizeof(No));
    novo_no->tarefa = tarefa;

    if (vaziaFila(fila)) {
        fila->fim = novo_no;
        fila->inicio = novo_no;
        novo_no->proximo_no = NULL;
    } else {
        fila->fim->proximo_no = novo_no;
        fila->fim = novo_no;
        fila->fim->proximo_no = NULL;
    }
}
