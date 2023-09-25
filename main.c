#include "estruturas.h"

void printaDiv() {
    printf("\n");
    for (int i = 0; i < 50; i++) {
        printf("=");
    }
    printf("\n");
}

Tarefa * criaTarefa(int * codigo_atual);

int main() {
    int codigo_atual = 0;

    //Cria as filas de tarefas por prioridade
    Fila * filas[3];
    for (int i = 0; i < 3; i++) {
        filas[i] = criaFila(); 
    }

    //Cria lista de pendentes
    Lista * pendentes = criaLista();

    return 0;
}

Tarefa * criaTarefa(int * codigo_atual) {
    
    Tarefa * nova_tarefa = (Tarefa *) malloc(sizeof(Tarefa));

    printaDiv();
    printf("AREA DE CRIACAO DE TAREFA\n\n");

    //NOME
    printf("Digite o nome da tarefa: ");
    fflush(stdin);
    fgets(nova_tarefa->nome, 30, stdin);

    //PROJETO
    printf("\nDigite o nome do projeto: ");
    fflush(stdin);
    fgets(nova_tarefa->projeto, 30, stdin);

    //DATA INICIO
    printf("\nDigite a data de início:");
    printf("\nDia: "); fflush(stdin); scanf("%d", &nova_tarefa->inicio.dia);
    printf("Mes: "); fflush(stdin); scanf("%d", &nova_tarefa->inicio.mes);
    printf("Ano: "); fflush(stdin); scanf("%d", &nova_tarefa->inicio.ano);

    //DATA TERMINO
    printf("\nDigite a data de termino:");
    printf("\nDia: "); fflush(stdin); scanf("%d", &nova_tarefa->termino.dia);
    printf("Mes: "); fflush(stdin); scanf("%d", &nova_tarefa->termino.mes);
    printf("Ano: "); fflush(stdin); scanf("%d", &nova_tarefa->termino.ano);

    //STATUS
    printf("\nDigite o status da tarefa ([1] => atrasada; [0] => em dia; [-1] => pendente)\n> "); 
    fflush(stdin); 
    scanf("%d", &nova_tarefa->status);

    //PRIORIDADE
    printf("\nDigite a prioridade da tarefa ([1] => Alta; [2] => Media; [3] => Baixa)\n> ");
    fflush(stdin);
    scanf("%d", &nova_tarefa->prioridade);
    getchar();

    //CODIGO
    nova_tarefa->codigo = *codigo_atual;
    printf("\nO codigo da tarefa eh: %d", *codigo_atual);
    printaDiv();

    (*codigo_atual)++;

    return nova_tarefa;
}
