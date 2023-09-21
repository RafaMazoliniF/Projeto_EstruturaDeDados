#include "estruturas.h"

void printaDiv() {
    printf("\n");
    for (int i = 0; i < 50; i++) printf("=");
    printf("\n");
}

Tarefa criaTarefa(int codigo, char nome[], char projeto[], int dia_inicio, int mes_inicio, int ano_inicio, int dia_fim, int mes_fim, int ano_fim, int status, int prioridade);
void insereTarefa(Tarefa tarefa, Fila * filas[], int * codigo_atual);
void alteraTarefa(int codigo, Fila * filas[], Lista * pendentes);

int main () {
    int codigo_atual = 0;

    //Cria as 3 filas por prioridade e coloca-as num vetor
    Fila * filas[3];
    for (int i = 0; i < 3; i++) {
        filas[i] = criaFila();
    }

    Lista * lista_pendentes = criaLista();

    alteraTarefa(1, filas, lista_pendentes);

    return 0;
}

//Cria uma nova tarefa e insere as suas informacoes
Tarefa criaTarefa(int codigo, char nome[], char projeto[], int dia_inicio, int mes_inicio, int ano_inicio, int dia_fim, int mes_fim, int ano_fim, int status, int prioridade) {
    Tarefa nova_tarefa;
    nova_tarefa.codigo = codigo;
    strcpy(nova_tarefa.nome, nome);
    strcpy(nova_tarefa.projeto, projeto);
    nova_tarefa.data_incio.dia = dia_inicio;
    nova_tarefa.data_incio.mes = mes_inicio;
    nova_tarefa.data_incio.ano = ano_inicio;
    nova_tarefa.data_fim.dia = dia_fim;
    nova_tarefa.data_fim.mes = mes_fim;
    nova_tarefa.data_fim.ano = ano_fim;
    nova_tarefa.status = status;
    nova_tarefa.prioridade = prioridade;

    return nova_tarefa;
}

//Insere uma tarefa na fila de tarefas correta
void insereTarefa(Tarefa tarefa, Fila * filas[], int * codigo_atual) {
    insereFila(filas[tarefa.prioridade - 1], tarefa);
    *codigo_atual++;
}

Tarefa getTarefa(int codigo, Fila * filas[], Lista * pendentes) {
    for (int i = 0; i < 3; i++) {
        No * no_atual = filas[i]->fim;
        while (no_atual != NULL) {
            if (no_atual->tarefa.codigo == codigo) return no_atual->tarefa;
            no_atual = no_atual->proximo_no;
        }
    }

    while (pendentes != NULL) {
        if (pendentes->tarefa.codigo == codigo) return pendentes->tarefa;
        pendentes = pendentes->proximo_no;
    }

    Tarefa tarefa_vazia;
    return tarefa_vazia;
}

void alteraTarefa(int codigo, Fila * filas[], Lista * pendentes) {
    printaDiv();
    printf("AREA DE ALTERACO DE DADOS\n\n");
    printf("Digite para alterar:\n[1]Nome da tarefa\n[2]Nome do projeto\n[3]Data de inicio\n[4]Data de termino\n[5]Status\n[6]Prioridade\n\n> ");

    int escolha;
    fflush(stdin);
    scanf("%d", &escolha);

    Tarefa tarefa = getTarefa(codigo, filas, pendentes);

    switch (escolha) {
        case 1:
            printf("\nNovo nome: ");
            tarefa.nome = gets();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default: printf("Escolha inválida. Nenhuma alteracao foi feita.");
    }

    printaDiv();
}   