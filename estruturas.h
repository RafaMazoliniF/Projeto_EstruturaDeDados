#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int codigo;
    char nome[30];
    char projeto[30];
    Data data_incio;
    Data data_fim;
    int status; // 1 => atrasado; 0 => em dia; -1 => pendente;
    int prioridade; // 1 => alta; 2 => media; 3 => baixa;
} Tarefa;

typedef struct No{
    struct No * proximo_no;
    Tarefa tarefa;
} No;


//*FILA
typedef struct Fila {
    No * inicio;
    No * fim;
} Fila;


//Inicializa uma fila com 0 nos
Fila * criaFila() {
    Fila * nova_fila = (Fila *) malloc(sizeof(Fila));
    nova_fila->inicio = NULL;
    nova_fila->fim = NULL;

    return nova_fila;
}

//Retorna se a fila esta vazia
bool vaziaFila(Fila * fila) {
    if (fila->inicio == NULL) return true;
    return false;
}

//Insere uma tarefa no final da fila
void insereFila(Fila * fila, Tarefa tarefa) {
    No * novo_no = (No *) malloc(sizeof(No));
    novo_no->tarefa = tarefa;

    if (vaziaFila(fila)) {
        fila->fim = novo_no;
        fila->inicio = novo_no;
        novo_no->proximo_no = NULL;
    } else {
        novo_no->proximo_no = fila->fim;
        fila->fim = novo_no;
    }
}

//*LISTA
typedef No Lista;

//Inicia uma lista com 0 nos
Lista * criaLista() {
    return NULL;
}

//Retorna true se a lista estiver vazia e false se não
bool vaziaLista(Lista * lista) {
    if (lista == NULL) return true;
    return false;
}

//retorna o no na posicao indicada:
// [-1] -> ultimo no; [nao existe] -> ultimo no; 
No * getNo(Lista * lista, int posicao) {
    if (posicao == -1) {
        if (vaziaLista(lista)) return lista;

        while (lista->proximo_no != NULL) {
            lista = lista->proximo_no;
        }

        return lista;
    }

    else {
        for (int i = 0; i < posicao; i++) {
            lista = lista->proximo_no;
            if (lista->proximo_no == NULL) {
                return lista;
            }
        }
    }

    return lista;
}


//Insere um no em qualquer posicao da lista:
// [-1] -> final; [nao existe] -> final;
void insereLista(Lista ** lista, Tarefa tarefa, int posicao) {
    No * novo_no = (No *) malloc(sizeof(No));

    if (posicao == 0) {
        if (vaziaLista(*lista)) {
            novo_no->tarefa = tarefa;
            novo_no->proximo_no = NULL;
            *lista = novo_no;
        } else {
            novo_no->tarefa = tarefa;
            novo_no->proximo_no = *lista;
            *lista = novo_no;
        }
    }

    else if (posicao > 0) {
        No * no_anterior = getNo(*lista, posicao - 1);
        novo_no->tarefa = tarefa;
        novo_no->proximo_no = no_anterior->proximo_no;
        no_anterior->proximo_no = novo_no;
    }

    else if (posicao == -1) {
        if (vaziaLista(*lista)) {
            *lista = novo_no;
            novo_no->tarefa = tarefa;
            novo_no->proximo_no = NULL;
        }

        else {
            No * ultimo_no = getNo(*lista, -1);
            ultimo_no->proximo_no = novo_no;
            novo_no->proximo_no = NULL;
            novo_no->tarefa = tarefa;
        }
    }
}
