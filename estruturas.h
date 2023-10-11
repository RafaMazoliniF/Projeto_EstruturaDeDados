#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void limpaBuffer() {
    #ifdef __linux__
        __fpurge(stdin);
    #elif _WIN32
        fflush(stdin);
    #else
    #endif
}

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

//Printa todos os codigos da lista seguindo a ordem. Concluida é um booleano que diz se a lista é de tarefas concluidas.
void printaLista(Lista * lista, bool concluida) {
    if (!vaziaLista(lista)) {
        if (concluida) {
            Lista * lista_aux = lista;

            printf("\nCONCLUIDAS COM ATRASO\n");
            while (!vaziaLista(lista)) {
                if (lista->tarefa->status == 1) 
                    printaTarefa(*(lista->tarefa));
                lista = lista->proximo_no;
            }

            lista = lista_aux;

            printf("\nCONCLUIDAS SEM ATRASOS\n");
            while (!vaziaLista(lista)) {
                if (lista->tarefa->status == 0) 
                    printaTarefa(*(lista->tarefa));
                lista = lista->proximo_no;
            }
            
        } else {
            while (!vaziaLista(lista)) {
                printaTarefa(*(lista->tarefa));
                lista = lista->proximo_no;
            }
        }
    }

    else printf("\nEsta lista esta vazia.\n");
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

//Se a lista não for vazia, retria e retorna o nó da frente.
No * desenfila(Fila * fila) {
    if (!vaziaFila(fila)) {
        No * no_retirado = fila->inicio;
        fila->inicio = fila->inicio->proximo_no;
        return no_retirado;
    }

    return NULL;
}

//Printa todas as tarefas de uma dada fila
void printaFila(Fila * fila) {
    No * inicio = fila->inicio;
    if (!vaziaFila(fila)) {
        while (inicio != NULL) {
            printaTarefa(*(inicio->tarefa));
            inicio = inicio->proximo_no;
        }
    }

    else printf("\nEsta fila está vazia.\n");
}

//Cria uma nova tarefa e retorna a mesma
Tarefa * criaTarefa(int * codigo_atual, int hoje[]) {
    
    Tarefa * nova_tarefa = (Tarefa *) malloc(sizeof(Tarefa));

    printaDiv();
    printf("AREA DE CRIACAO DE TAREFA\n\n");

    //NOME
    printf("Digite o nome da tarefa: ");
    limpaBuffer();
    fgets(nova_tarefa->nome, 30, stdin);
    int nome_i = 0;
    while (nova_tarefa->nome[nome_i] != '\n') nome_i++;
    nova_tarefa->nome[nome_i] = '\0';

    //PROJETO
    printf("\nDigite o nome do projeto: ");
    fgets(nova_tarefa->projeto, 30, stdin);
    int projeto_i = 0;
    while (nova_tarefa->projeto[projeto_i] != '\n') projeto_i++;
    nova_tarefa->projeto[projeto_i] = '\0';

    //DATA INICIO
    printf("\nData de início: %d/%d/%d", hoje[0], hoje[1], hoje[2]);
    nova_tarefa->inicio.dia = hoje[0];
    nova_tarefa->inicio.mes = hoje[1];
    nova_tarefa->inicio.ano = hoje[2];

    //DATA TERMINO
    printf("\nDigite a data de termino:");
    printf("\nDia: "); limpaBuffer(); scanf("%d", &nova_tarefa->termino.dia);
    printf("Mes: "); limpaBuffer(); scanf("%d", &nova_tarefa->termino.mes);
    printf("Ano: "); limpaBuffer(); scanf("%d", &nova_tarefa->termino.ano);

    //STATUS
    if (dataMenor(nova_tarefa->termino, nova_tarefa->inicio)) nova_tarefa->status = 1;
    else nova_tarefa->status = 0;

    //PRIORIDADE
    printf("\nDigite a prioridade da tarefa ([1] => Alta; [2] => Media; [3] => Baixa)\n> ");
    limpaBuffer();
    scanf("%d", &nova_tarefa->prioridade);
    getchar();

    //CODIGO
    nova_tarefa->codigo = *codigo_atual;
    printf("\nO codigo da tarefa eh: %d", *codigo_atual);
    printaDiv();

    (*codigo_atual)++;

    return nova_tarefa;
}

//Recebe uma tarefa e insere em uma das filas ou na lista de pendentes
void cadastraNovaTarefa(Fila ** filas, Tarefa * tarefa) {
    insereFila(filas[tarefa->prioridade - 1], tarefa);
}

//retorna a tarefa com o código passado
Tarefa * getTarefa(int codigo, Lista * pendentes, Fila ** filas) {
    while (pendentes != NULL) {
        if (pendentes->tarefa->codigo == codigo) return pendentes->tarefa;
        pendentes = pendentes->proximo_no;
    }

    for (int i = 0; i < 3; i++) {
        No * no_atual = filas[i]->inicio;
        while (no_atual != NULL) {
            if (no_atual->tarefa->codigo == codigo) return no_atual->tarefa;
            no_atual = no_atual->proximo_no;
        }
    }

    return NULL; // Default
}

//Retira a tarefa com o dado código de onde ela estiver (Seja uma fila ou lista)
No * retiraTarefa(int codigo, Lista ** pendentes, Fila ** filas) {
    Tarefa * tarefa = getTarefa(codigo, *pendentes, filas);
    No * no_excluido;
    
    //Procura na lista de pendentes
    if (tarefa->status == -1) {

        if ((*pendentes)->tarefa == tarefa) {
            no_excluido = *pendentes;
            (*pendentes) = (*pendentes)->proximo_no;
        }

        else {
            Lista * pendentes_aux = *pendentes;

            while(pendentes_aux->proximo_no->tarefa != tarefa && pendentes_aux->proximo_no != NULL) {
                pendentes_aux = pendentes_aux->proximo_no;
            }

            no_excluido = pendentes_aux->proximo_no;
            pendentes_aux->proximo_no = pendentes_aux->proximo_no->proximo_no;
        }
    }

    else {
        Fila * fila = filas[tarefa->prioridade - 1];

        if (fila->inicio->tarefa == tarefa) {
            no_excluido = fila->inicio;
            fila->inicio = fila->inicio->proximo_no;
        }

        else {
            No * no_aux;

            bool achou_tarefa = false;
            while (!achou_tarefa) {
                no_aux = desenfila(fila);
                if (no_aux->tarefa->codigo == codigo) {
                    no_excluido = no_aux;
                    achou_tarefa = true;
                } else {
                    insereFila(fila, no_aux->tarefa);
                    free(no_aux);
                }
            }
        }
    }

    return no_excluido;
}

//Libera a memória de uma tarefa 
void deletaTarefa(int codigo, Lista ** pendentes, Fila ** filas) {
    No * no_liberado = retiraTarefa(codigo, pendentes, filas);
    free(no_liberado->tarefa);
    free(no_liberado);
}

//Recebe o codigo de uma tarefa e altera as suas informacoes
void editaTarefa(int codigo, Fila ** filas, Lista ** pendentes) {
    Tarefa * tarefa = getTarefa(codigo, *pendentes, filas);
    
    printaDiv();
    printf("AREA DE EDICAO DE TAREFA\n\n");

    printf("Para editar, digite:\n[0] Nome\n[1] Projeto;\n[2] Data de inicio;\n[3] Data de termino;\n[4] Status;\n[5] Prioridade;\n> ");
    int escolha;
    limpaBuffer();
    scanf("%d", &escolha);

    switch (escolha) {
        case 0:
            printf("\nNovo nome: ");
            limpaBuffer();
            fgets(tarefa->nome, 30, stdin);
            int nome_i = 0;
            while (tarefa->nome[nome_i] != '\n') nome_i++;
            tarefa->nome[nome_i] = '\0';
            break;
        case 1:
            printf("\nNovo projeto: ");
            limpaBuffer();
            fgets(tarefa->projeto, 30, stdin);
            int projeto_i = 0;
            while (tarefa->projeto[projeto_i] != '\n') projeto_i++;
            tarefa->projeto[projeto_i] = '\0';
            break;
        case 2:
            printf("Nova data de inicio:");
            printf("\nDia: "); limpaBuffer(); scanf("%d", &tarefa->inicio.dia);
            printf("Mes: "); limpaBuffer(); scanf("%d", &tarefa->inicio.mes);
            printf("Ano: "); limpaBuffer(); scanf("%d", &tarefa->inicio.ano);
            break;
        case 3:
            printf("Nova data de termino:");
            printf("\nDia: "); limpaBuffer(); scanf("%d", &tarefa->termino.dia);
            printf("Mes: "); limpaBuffer(); scanf("%d", &tarefa->termino.mes);
            printf("Ano: "); limpaBuffer(); scanf("%d", &tarefa->termino.ano);
            break;
        case 4:
            printf("Novo status: ");
            limpaBuffer();
            int status_atualizado;
            scanf("%d", &status_atualizado);

            if (status_atualizado == -1) {
                free(retiraTarefa(codigo, pendentes, filas));
                insereLista(pendentes, tarefa);
            }

            else if(status_atualizado == 0 || status_atualizado == 1) {
                free(retiraTarefa(codigo, pendentes, filas));
                insereFila(filas[tarefa->prioridade - 1], tarefa);
            }
    
            tarefa->status = status_atualizado;

            break;
        case 5:
            printf("Nova prioridade: ");
            limpaBuffer();
            free(retiraTarefa(codigo, pendentes, filas));
            scanf("%d", &tarefa->prioridade);
            insereFila(filas[tarefa->prioridade -1], tarefa);
            break;
        default: 
            printf("Escolha invalida");
            break;
        
    }

    if (dataMenor(tarefa->termino, tarefa->inicio) && tarefa->status != -1) tarefa->status = 1;

    printaDiv();
}
